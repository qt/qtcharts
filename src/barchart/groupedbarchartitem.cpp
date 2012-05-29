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

#include "groupedbarchartitem_p.h"
#include "bar_p.h"
#include "qbarset_p.h"
#include "qbarseries_p.h"
#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

GroupedBarChartItem::GroupedBarChartItem(QBarSeries *series, ChartPresenter *presenter) :
    BarChartItem(series, presenter)
{
}

QVector<QRectF> GroupedBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accurancy
    qreal categoryCount = m_series->categoryCount();
    qreal setCount = m_series->barsetCount();

    // Domain:
    qreal width = geometry().width();
    qreal height = geometry().height();
    qreal rangeY = m_domainMaxY - m_domainMinY;
    qreal rangeX = m_domainMaxX - m_domainMinX;
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);
    qreal categoryWidth = width / categoryCount;
    qreal barWidth = categoryWidth / setCount - (categoryWidth / setCount) * m_series->d_func()->barMargin();

    int itemIndex(0);
    for (int category = 0; category < categoryCount; category++) {
        qreal yPos = height + scaleY * m_domainMinY + geometry().topLeft().y();
        for (int set = 0; set < setCount; set++) {
            QBarSet* barSet = m_series->d_func()->barsetAt(set);

            qreal xPos = (barSet->at(category).x() - m_domainMinX) * scaleX + m_rect.left();
            xPos -= setCount*barWidth/2;
            xPos += set*barWidth;
            qreal barHeight = barSet->at(category).y() * scaleY;
            Bar* bar = m_bars.at(itemIndex);

            QRectF rect(xPos, yPos - barHeight, barWidth, barHeight);
            layout.append(rect);
            bar->setPen(barSet->pen());
            bar->setBrush(barSet->brush());

            QGraphicsSimpleTextItem* label = m_labels.at(itemIndex);

            if (!qFuzzyIsNull(barSet->at(category).y())) {
                label->setText(QString::number(barSet->at(category).y()));
            } else {
                label->setText(QString(""));
            }

            label->setPos(xPos + (rect.width()/2 - label->boundingRect().width()/2)
                          ,yPos - barHeight/2 - label->boundingRect().height()/2);
            label->setFont(barSet->labelFont());

            itemIndex++;
        }
    }
    return layout;
}

#include "moc_groupedbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
