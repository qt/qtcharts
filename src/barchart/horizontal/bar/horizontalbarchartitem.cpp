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

#include "horizontalbarchartitem_p.h"
#include "qabstractbarseries_p.h"
#include "qbarset_p.h"
#include "bar_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalBarChartItem::HorizontalBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item)
    : AbstractBarChartItem(series, item)
{
}

QVector<QRectF> HorizontalBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accuracy
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
//    bool barsVisible = m_series->isVisible();
    qreal barWidth = m_series->d_func()->barWidth();

    int itemIndex(0);
    for(int category = 0; category < categoryCount; category++) {
        for (int set = 0; set < setCount; set++) {
            qreal value = m_series->barSets().at(set)->at(category);
            QRectF rect;
            QPointF topLeft;
            if (domain()->type() == AbstractDomain::LogXYDomain
                    || domain()->type() == AbstractDomain::LogXLogYDomain)
                topLeft = domain()->calculateGeometryPoint(QPointF(domain()->minX(), category - barWidth / 2 + (set + 1)/(setCount) * barWidth));
            else
                topLeft = domain()->calculateGeometryPoint(QPointF(0, category - barWidth / 2 + (set + 1)/(setCount) * barWidth));

            QPointF bottomRight = domain()->calculateGeometryPoint(QPointF(value, category - barWidth / 2 + (set)/(setCount) * barWidth));
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect);

            QGraphicsSimpleTextItem *label = m_labels.at(itemIndex);
            label->setZValue(200);
            itemIndex++;
            if (!qFuzzyCompare(value, 0))
                label->setText(QString::number(value));
            else
                label->setText(QString(""));

//            label->setFont(m_series->barSets().at(set)->labelFont());
//            label->setBrush(m_series->barSets().at(set)->labelBrush());
            label->setBrush(Qt::black);

            label->setPos(rect.center() - label->boundingRect().center());

        }
    }


//    // AbstractDomain:
//    qreal width = geometry().width();
//    qreal height = geometry().height();
//    qreal rangeY = m_domainMaxY - m_domainMinY;
//    qreal rangeX = m_domainMaxX - m_domainMinX;
//    qreal scaleY = (height / rangeY);
//    qreal scaleX = (width / rangeX);

//    // On horizontal chart barWidth of the barseries means height of the rect.
//    qreal rectHeight = (scaleY / setCount) * m_series->d_func()->barWidth();

//    int itemIndex(0);
//    for (int category = 0; category < categoryCount; category++) {
//        qreal xPos = -scaleX * m_domainMinX + geometry().left();
//        for (int set = 0; set < setCount; set++) {
//            QBarSetPrivate *barSet = m_series->d_func()->barsetAt(set)->d_ptr.data();

//            qreal yPos = geometry().bottom() + (m_domainMinY - barSet->pos(category)) * scaleY;
//            yPos += setCount * rectHeight / 2;
//            yPos -= set * rectHeight;

//            qreal rectWidth = barSet->value(category) * scaleX;
//            Bar *bar = m_bars.at(itemIndex);

//            QRectF rect(xPos, yPos - rectHeight, rectWidth, rectHeight);
//            layout.append(rect);
//            bar->setPen(barSet->m_pen);
//            bar->setBrush(barSet->m_brush);
//            if (qFuzzyCompare(rectHeight, 0))
//                bar->setVisible(false);
//            else
//                bar->setVisible(barsVisible);

//            QGraphicsSimpleTextItem *label = m_labels.at(itemIndex);

//            if (!qFuzzyCompare(barSet->value(category), 0))
//                label->setText(QString::number(barSet->value(category)));
//            else
//                label->setText(QString(""));

//            label->setPos(xPos + (rect.width() / 2 - label->boundingRect().width() / 2),
//                          yPos - rectHeight / 2 - label->boundingRect().height() / 2);
//            label->setFont(barSet->m_labelFont);
//            label->setBrush(barSet->m_labelBrush);

//            itemIndex++;
//        }
//    }
    return layout;
}

#include "moc_horizontalbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
