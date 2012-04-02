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

#include "stackedbarchartitem_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartItem::StackedBarChartItem(QBarSeries *series, ChartPresenter *presenter) :
    BarChartItem(series, presenter)
{
}

StackedBarChartItem::~StackedBarChartItem()
{
}

QVector<QRectF> StackedBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;
    // Use temporary qreals for accurancy (we might get some compiler warnings... :)

    qreal maxSum = m_series->maxCategorySum();
    // Domain:
    if (m_domainMaxY > maxSum) {
        maxSum = m_domainMaxY;
    }

    qreal height = geometry().height();
    qreal width = geometry().width();
    qreal scale = (height /  m_series->maxCategorySum());
    qreal categotyCount = m_series->categoryCount();
    qreal barWidth = width / (categotyCount * 2);
    qreal xStep = width / categotyCount;
    qreal xPos = xStep / 2 - barWidth / 2;

    int itemIndex(0);
    for (int category = 0; category < categotyCount; category++) {
        qreal yPos = height;
        for (int set=0; set < m_series->barsetCount(); set++) {
            QBarSet* barSet = m_series->barsetAt(set);

            qreal barHeight = barSet->valueAt(category) * scale; //m_series->valueAt(set, category) * scale;
            Bar* bar = m_bars.at(itemIndex);
            bar->setPen(barSet->pen());
            bar->setBrush(barSet->brush());
            QRectF rect(xPos, yPos-barHeight, barWidth, barHeight);
            layout.append(rect);

            BarValue* value = m_values.at(itemIndex);

            if (!qFuzzyIsNull(barSet->valueAt(category))) {
                value->setText(QString::number(barSet->valueAt(category)));
            } else {
                value->setText(QString(""));
            }

            value->setPos(xPos + (rect.width()/2 - value->boundingRect().width()/2)
                          ,yPos - barHeight/2 - value->boundingRect().height()/2);
            value->setPen(barSet->valuePen());

            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }

    return layout;
}

#include "moc_stackedbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
