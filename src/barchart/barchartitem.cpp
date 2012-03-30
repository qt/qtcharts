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

#include "barchartitem_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include "qbarseries.h"
#include "qchart.h"
#include "qchartaxis.h"
#include "qchartaxiscategories.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include "chartdataset_p.h"
#include <QDebug>
#include <QToolTip>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartItem::BarChartItem(QBarSeries *series, ChartPresenter *presenter) :
    ChartItem(presenter),
    m_layoutSet(false),
    m_series(series)
{
    connect(series, SIGNAL(showToolTip(QPoint,QString)), this, SLOT(showToolTip(QPoint,QString)));
    connect(series, SIGNAL(updatedBars()), this, SLOT(handleLayoutChanged()));
//TODO:  connect(series,SIGNAL("position or size has changed"), this, SLOT(handleLayoutChanged()));
    connect(series, SIGNAL(restructuredBar(int)), this, SLOT(handleModelChanged(int)));
    setZValue(ChartPresenter::BarSeriesZValue);
    dataChanged();
}

BarChartItem::~BarChartItem()
{
    disconnect(this,SLOT(showToolTip(QPoint,QString)));
}

void BarChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!m_layoutSet) {
        qWarning() << "BarChartItem::paint called without layout set. Aborting.";
        return;
    }

    foreach(QGraphicsItem* i, childItems())
        i->paint(painter,option,widget);
}

QRectF BarChartItem::boundingRect() const
{
    return m_rect;
}

void BarChartItem::dataChanged()
{
    // TODO: performance optimizations. Do we really need to delete and create items every time data is changed or can we reuse them?
    // Delete old bars
    foreach (QGraphicsItem *item, childItems())
        delete item;

    m_bars.clear();
    m_floatingValues.clear();
    m_layout.clear();

    // Create new graphic items for bars
    for (int c = 0; c < m_series->categoryCount(); c++) {
        QString category = m_series->categoryName(c);
        for (int s = 0; s < m_series->barsetCount(); s++) {
            QBarSet *set = m_series->barsetAt(s);
            Bar *bar = new Bar(category,this);
            childItems().append(bar);
            m_bars.append(bar);
            connect(bar, SIGNAL(clicked(QString)), set, SIGNAL(clicked(QString)));
            connect(bar, SIGNAL(rightClicked(QString)), set, SIGNAL(rightClicked(QString)));
            connect(bar, SIGNAL(hoverEntered(QPoint)), set, SLOT(barHoverEnterEvent(QPoint)));
            connect(bar, SIGNAL(hoverLeaved()), set, SLOT(barHoverLeaveEvent()));
            m_layout.append(QRectF(0, 0, 0, 0));
        }
    }

    // Create floating values
    for (int category = 0; category < m_series->categoryCount(); category++) {
        for (int s = 0; s < m_series->barsetCount(); s++) {
            QBarSet *set = m_series->barsetAt(s);
            BarValue *value = new BarValue(*set, this);
            childItems().append(value);
            m_floatingValues.append(value);
            connect(set, SIGNAL(toggleFloatingValues()), value, SLOT(toggleVisible()));
        }
    }
}

QVector<QRectF> BarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accurancy (we might get some compiler warnings... :)
    qreal categoryCount = m_series->categoryCount();
    qreal setCount = m_series->barsetCount();

    qreal width = geometry().width();
    qreal height = geometry().height();

    qreal max = m_series->max();

    // Domain:
    if (m_domainMaxY > max) {
        max = m_domainMaxY;
    }

    qreal scale = (height / max);
    qreal categoryWidth = width / categoryCount;
    qreal barWidth = categoryWidth / (setCount+1);

    int itemIndex(0);
    for (int category = 0; category < categoryCount; category++) {
        qreal xPos = categoryWidth * category + barWidth / 2;
        qreal yPos = height;
        for (int set = 0; set < setCount; set++) {
            qreal barHeight = m_series->valueAt(set, category) * scale;
            Bar* bar = m_bars.at(itemIndex);

            QRectF rect(xPos, yPos - barHeight, barWidth, barHeight);
            layout.append(rect);
            bar->setPen(m_series->barsetAt(set)->pen());
            bar->setBrush(m_series->barsetAt(set)->brush());
            itemIndex++;
            xPos += barWidth;
        }
    }

    // Position floating values
    itemIndex = 0;
    for (int category = 0; category < m_series->categoryCount(); category++) {
        qreal xPos = categoryWidth * category  + barWidth;
        qreal yPos = height;
        for (int set=0; set < m_series->barsetCount(); set++) {
            qreal barHeight = m_series->valueAt(set, category) * scale;
            BarValue* value = m_floatingValues.at(itemIndex);

            QBarSet* barSet = m_series->barsetAt(set);

            if (!qFuzzyIsNull(m_series->valueAt(set,category))) {
                value->setText(QString::number(m_series->valueAt(set, category)));
            } else {
                value->setText(QString(""));
            }

            value->setPos(xPos, yPos-barHeight / 2);
            value->setPen(barSet->floatingValuePen());

            itemIndex++;
            xPos += barWidth;
        }
    }

    return layout;
}

void BarChartItem::applyLayout(const QVector<QRectF> &layout)
{
    if (animator())
        animator()->updateLayout(this, m_layout, layout);
    else
        setLayout(layout);
}

void BarChartItem::setLayout(const QVector<QRectF> &layout)
{
    m_layout = layout;

    for (int i=0; i < m_bars.count(); i++)
        m_bars.at(i)->setRect(layout.at(i));

    update();
}

//handlers

void BarChartItem::handleModelChanged(int index)
{
    Q_UNUSED(index)
    dataChanged();
}

void BarChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_domainMinX = minX;
    m_domainMaxX = maxX;
    m_domainMinY = minY;
    m_domainMaxY = maxY;
    handleLayoutChanged();
}

void BarChartItem::handleGeometryChanged(const QRectF &rect)
{
    m_rect = rect;
    handleLayoutChanged();
    m_layoutSet = true;
    setPos(rect.topLeft());
}

void BarChartItem::handleLayoutChanged()
{
    QVector<QRectF> layout = calculateLayout();
    applyLayout(layout);
    update();
}

void BarChartItem::showToolTip(QPoint pos, QString tip)
{
    // TODO: cool tooltip instead of default
    QToolTip::showText(pos, tip);
}

#include "moc_barchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
