/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "abstractbarchartitem_p.h"
#include "bar_p.h"
#include "qbarset.h"
#include "qbarset_p.h"
#include "qabstractbarseries.h"
#include "qabstractbarseries_p.h"
#include "qchart.h"
#include "chartpresenter_p.h"
#include "charttheme_p.h"
#include "baranimation_p.h"
#include "chartdataset_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AbstractBarChartItem::AbstractBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    ChartItem(series->d_func(),item),
    m_animation(0),
    m_series(series)
{

    setFlag(ItemClipsChildrenToShape);
    connect(series->d_func(), SIGNAL(updatedLayout()), this, SLOT(handleLayoutChanged()));
    connect(series->d_func(), SIGNAL(updatedBars()), this, SLOT(handleUpdatedBars()));
    connect(series->d_func(), SIGNAL(labelsVisibleChanged(bool)), this, SLOT(handleLabelsVisibleChanged(bool)));
    connect(series->d_func(), SIGNAL(restructuredBars()), this, SLOT(handleDataStructureChanged()));
    connect(series, SIGNAL(visibleChanged()), this, SLOT(handleVisibleChanged()));
    connect(series, SIGNAL(opacityChanged()), this, SLOT(handleOpacityChanged()));
    setZValue(ChartPresenter::BarSeriesZValue);
    handleDataStructureChanged();
    handleVisibleChanged();
    handleUpdatedBars();
}

AbstractBarChartItem::~AbstractBarChartItem()
{
}

void AbstractBarChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF AbstractBarChartItem::boundingRect() const
{
    return m_rect;
}

void AbstractBarChartItem::applyLayout(const QVector<QRectF> &layout)
{
    QSizeF size = geometry().size();
    if (geometry().size().isValid()) {
        if (m_animation) {
            if (m_layout.count() == 0 || m_oldSize != size) {
                initializeLayout();
                m_oldSize = size;
            }
            m_animation->setup(m_layout, layout);
            presenter()->startAnimation(m_animation);
        } else {
            setLayout(layout);
            update();
        }
    }
}

void AbstractBarChartItem::setAnimation(BarAnimation *animation)
{
    m_animation = animation;
}

void AbstractBarChartItem::setLayout(const QVector<QRectF> &layout)
{
    if (layout.count() != m_bars.count())
        return;

    m_layout = layout;

    for (int i = 0; i < m_bars.count(); i++) {
        m_bars.at(i)->setRect(layout.at(i));
        QGraphicsSimpleTextItem *label = m_labels.at(i);
        label->setPos(layout.at(i).center() - label->boundingRect().center());

    }
}
//handlers

void AbstractBarChartItem::handleDomainUpdated()
{
    m_domainMinX = domain()->minX();
    m_domainMaxX = domain()->maxX();
    m_domainMinY = domain()->minY();
    m_domainMaxY = domain()->maxY();

    QRectF rect(QPointF(0,0),domain()->size());

    if(m_rect != rect){
        prepareGeometryChange();
        m_rect = rect;
    }

    handleLayoutChanged();
}

void AbstractBarChartItem::handleLayoutChanged()
{
    if ((m_rect.width() <= 0) || (m_rect.height() <= 0))
        return; // rect size zero.
    QVector<QRectF> layout = calculateLayout();
    applyLayout(layout);
    handleUpdatedBars();
}

void AbstractBarChartItem::handleLabelsVisibleChanged(bool visible)
{
    foreach (QGraphicsSimpleTextItem *label, m_labels)
        label->setVisible(visible);
    update();
}

void AbstractBarChartItem::handleDataStructureChanged()
{
    foreach (QGraphicsItem *item, childItems())
        delete item;

    m_bars.clear();
    m_labels.clear();
    m_layout.clear();

    // Create new graphic items for bars
    for (int c = 0; c < m_series->d_func()->categoryCount(); c++) {
        for (int s = 0; s < m_series->count(); s++) {
            QBarSet *set = m_series->d_func()->barsetAt(s);

            // Bars
            Bar *bar = new Bar(set, c, this);
            m_bars.append(bar);
            connect(bar, SIGNAL(clicked(int,QBarSet*)), m_series, SIGNAL(clicked(int,QBarSet*)));
            connect(bar, SIGNAL(hovered(bool,QBarSet*)), m_series, SIGNAL(hovered(bool,QBarSet*)));
            connect(bar, SIGNAL(clicked(int,QBarSet*)), set, SIGNAL(clicked(int)));
            connect(bar, SIGNAL(hovered(bool,QBarSet*)), set, SIGNAL(hovered(bool)));
            //            m_layout.append(QRectF(0, 0, 1, 1));

            // Labels
            m_labels.append(new QGraphicsSimpleTextItem(this));
        }
    }

    if(themeManager()) themeManager()->updateSeries(m_series);
    handleLayoutChanged();
    handleVisibleChanged();
}

void AbstractBarChartItem::handleVisibleChanged()
{
    bool visible = m_series->isVisible();
    if (visible)
        handleLabelsVisibleChanged(m_series->isLabelsVisible());
    else
        handleLabelsVisibleChanged(visible);

    foreach (QGraphicsItem *bar, m_bars)
        bar->setVisible(visible);
}

void AbstractBarChartItem::handleOpacityChanged()
{
    foreach (QGraphicsItem *item, childItems())
        item->setOpacity(m_series->opacity());
}

void AbstractBarChartItem::handleUpdatedBars()
{
    // Handle changes in pen, brush, labels etc.
    int categoryCount = m_series->d_func()->categoryCount();
    int setCount = m_series->count();
    int itemIndex(0);

    for (int category = 0; category < categoryCount; category++) {
        for (int set = 0; set < setCount; set++) {
            QBarSetPrivate *barSet = m_series->d_func()->barsetAt(set)->d_ptr.data();
            Bar *bar = m_bars.at(itemIndex);
            bar->setPen(barSet->m_pen);
            bar->setBrush(barSet->m_brush);
            bar->update();

            QGraphicsSimpleTextItem *label = m_labels.at(itemIndex);
            label->setText(QString("%1").arg(barSet->value(category)));
            label->setFont(barSet->m_labelFont);
            label->setBrush(barSet->m_labelBrush);
            label->update();
            itemIndex++;
        }
    }
}

#include "moc_abstractbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
