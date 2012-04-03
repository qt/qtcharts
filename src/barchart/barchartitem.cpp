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
#include "barlabel_p.h"
#include "qbarset.h"
#include "qbarseries.h"
#include "qchart.h"
#include "qchartaxis.h"
#include "qchartaxiscategories.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include "chartdataset_p.h"
#include <QToolTip>
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartItem::BarChartItem(QBarSeries *series, ChartPresenter *presenter) :
    ChartItem(presenter),
    m_layoutSet(false),
    m_series(series)
{
    connect(series, SIGNAL(showToolTip(QPoint,QString)), this, SLOT(showToolTip(QPoint,QString)));
    connect(series, SIGNAL(updatedBars()), this, SLOT(handleLayoutChanged()));
    connect(series, SIGNAL(restructuredBars()), this, SLOT(handleModelChanged()));
    setZValue(ChartPresenter::BarSeriesZValue);
    dataChanged();
}

BarChartItem::~BarChartItem()
{
    disconnect(this,SLOT(showToolTip(QPoint,QString)));
    deleteItems();
}

void BarChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!m_layoutSet) {
        qWarning() << "BarChartItem::paint called without layout set. Aborting.";
        return;
    }

    painter->save();
    painter->setClipRect(m_clipRect);
    foreach (Bar *bar, m_bars)
        bar->paint(painter,option,widget);
    foreach (BarLabel* label, m_labels)
        label->paint(painter,option,widget);
    painter->restore();
}

QRectF BarChartItem::boundingRect() const
{
    return m_rect.translated(-m_rect.topLeft());
//    return m_rect;
}

void BarChartItem::dataChanged()
{
    // TODO: performance optimizations. Do we really need to delete and create items every time data is changed or can we reuse them?
    deleteItems();

    m_bars.clear();
    m_labels.clear();
    m_layout.clear();

    // Create new graphic items for bars
    for (int c = 0; c < m_series->categoryCount(); c++) {
        QString category = m_series->categoryName(c);
        for (int s = 0; s < m_series->barsetCount(); s++) {
            QBarSet *set = m_series->barsetAt(s);
            Bar *bar = new Bar(category,0);     // Null parent is best :)
            m_bars.append(bar);
            connect(bar, SIGNAL(clicked(QString,Qt::MouseButtons)), set, SIGNAL(clicked(QString,Qt::MouseButtons)));
            connect(bar, SIGNAL(hoverEntered(QPoint)), set, SLOT(barHoverEnterEvent(QPoint)));
            connect(bar, SIGNAL(hoverLeaved()), set, SLOT(barHoverLeaveEvent()));
            m_layout.append(QRectF(0, 0, 0, 0));
        }
    }

    // Create labels
    for (int category = 0; category < m_series->categoryCount(); category++) {
        for (int s = 0; s < m_series->barsetCount(); s++) {
            QBarSet *set = m_series->barsetAt(s);
            BarLabel *value = new BarLabel(*set, 0);
            m_labels.append(value);
            connect(set,SIGNAL(labelsVisibleChanged(bool)),value,SLOT(labelsVisibleChanged(bool)));
        }
    }
}

QVector<QRectF> BarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accurancy
    qreal categoryCount = m_series->categoryCount();
    qreal setCount = m_series->barsetCount();

    // Domain:
    qreal width = geometry().width();
    qreal height = geometry().height();
    qreal range = m_domainMaxY - m_domainMinY;
    qreal scale = (height / range);
    qreal categoryWidth = width / categoryCount;
    qreal barWidth = categoryWidth / (setCount+1);

    int itemIndex(0);
    for (int category = 0; category < categoryCount; category++) {
        qreal xPos = categoryWidth * category + barWidth / 2;
        qreal yPos = height + scale * m_domainMinY;
        for (int set = 0; set < setCount; set++) {
            QBarSet* barSet = m_series->barsetAt(set);

            qreal barHeight = barSet->valueAt(category) * scale;
            Bar* bar = m_bars.at(itemIndex);

            QRectF rect(xPos, yPos - barHeight, barWidth, barHeight);
            layout.append(rect);
            bar->setPen(barSet->pen());
            bar->setBrush(barSet->brush());

            BarLabel* label = m_labels.at(itemIndex);

            if (!qFuzzyIsNull(barSet->valueAt(category))) {
                label->setText(QString::number(barSet->valueAt(category)));
            } else {
                label->setText(QString(""));
            }

            label->setPos(xPos + (rect.width()/2 - label->boundingRect().width()/2)
                          ,yPos - barHeight/2 - label->boundingRect().height()/2);
            label->setFont(barSet->labelFont());

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

void BarChartItem::deleteItems()
{
    foreach (Bar *bar, m_bars)
        delete bar;
    foreach (BarLabel* label, m_labels)
        delete label;
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
    prepareGeometryChange();
    m_clipRect = rect.translated(-rect.topLeft());
    m_rect = rect;
    handleLayoutChanged();
    m_layoutSet = true;
    setPos(rect.topLeft());
}

void BarChartItem::handleLayoutChanged()
{
    if ((m_rect.width() <= 0) || (m_rect.height() <= 0)) {
        // rect size zero.
        return;
    }
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
