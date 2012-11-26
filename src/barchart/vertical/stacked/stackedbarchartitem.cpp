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
#include "qbarset_p.h"
#include "qabstractbarseries_p.h"
#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartItem::StackedBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    AbstractBarChartItem(series, item)
{
}

QVector<QRectF> StackedBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;
    // Use temporary qreals for accuracy
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
//    bool barsVisible = m_series->isVisible();
    qreal barWidth = m_series->d_func()->barWidth();

    for(int category = 0; category < categoryCount; category++) {
        qreal positiveSum = 0;
        qreal negativeSum = 0;
        for (int set = 0; set < setCount; set++) {
            qreal value = m_series->barSets().at(set)->at(category);
            QRectF rect;
            QPointF topLeft;
            QPointF bottomRight;
            if (value < 0) {
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2, value + negativeSum));
                if (domain()->type() == AbstractDomain::XLogYDomain
                        || domain()->type() == AbstractDomain::LogXLogYDomain)
                    topLeft = domain()->calculateGeometryPoint(QPointF(category + barWidth / 2, set ? negativeSum : domain()->minY()));
                else
                    topLeft = domain()->calculateGeometryPoint(QPointF(category + barWidth / 2, set ? negativeSum : 0));
                negativeSum += value;
            } else {
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2, value + positiveSum));
                if (domain()->type() == AbstractDomain::XLogYDomain
                        || domain()->type() == AbstractDomain::LogXLogYDomain)
                    topLeft = domain()->calculateGeometryPoint(QPointF(category + barWidth / 2, set ? positiveSum : domain()->minY()));
                else
                    topLeft = domain()->calculateGeometryPoint(QPointF(category + barWidth / 2, set ? positiveSum : 0));
                positiveSum += value;
            }
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect);
        }
    }


// AbstractDomain:
//    qreal width = geometry().width();
//    qreal height = geometry().height();
//    qreal rangeY = m_domainMaxY - m_domainMinY;
//    qreal rangeX = m_domainMaxX - m_domainMinX;
//    qreal scaleY = (height / rangeY);
//    qreal scaleX = (width / rangeX);
//    qreal rectWidth = scaleX * m_series->d_func()->barWidth();

//    int itemIndex(0);
//    for (int category = 0; category < categoryCount; category++) {
//        qreal yMax = height + scaleY * m_domainMinY + geometry().top();
//        qreal yMin = height + scaleY * m_domainMinY + geometry().top();
//        for (int set = 0; set < setCount; set++) {
//            QBarSetPrivate *barSet = m_series->d_func()->barsetAt(set)->d_ptr.data();

//            qreal xPos = (barSet->pos(category) - m_domainMinX) * scaleX + geometry().left() - rectWidth / 2;

//            qreal rectHeight = barSet->value(category) * scaleY;
//            Bar *bar = m_bars.at(itemIndex);
//            bar->setPen(barSet->m_pen);
//            bar->setBrush(barSet->m_brush);
//            if (qFuzzyIsNull(rectHeight))
//                bar->setVisible(false);
//            else
//                bar->setVisible(barsVisible);

//            QGraphicsSimpleTextItem *label = m_labels.at(itemIndex);

//            if (!qFuzzyIsNull(barSet->value(category)))
//                label->setText(QString::number(barSet->value(category)));
//            else
//                label->setText(QString(""));

//            label->setFont(barSet->m_labelFont);
//            label->setBrush(barSet->m_labelBrush);

//            if (rectHeight < 0) {
//                QRectF rect(xPos, yMax - rectHeight, rectWidth, rectHeight);
//                layout.append(rect);
//                label->setPos(xPos + (rect.width() / 2 - label->boundingRect().width() / 2),
//                              yMax - rectHeight / 2 - label->boundingRect().height() / 2);
//                yMax -= rectHeight;
//            } else {
//                QRectF rect(xPos, yMin - rectHeight, rectWidth, rectHeight);
//                layout.append(rect);
//                label->setPos(xPos + (rect.width() / 2 - label->boundingRect().width() / 2),
//                              yMin - rectHeight / 2 - label->boundingRect().height() / 2);
//                yMin -= rectHeight;
//            }

//            itemIndex++;
//        }
//    }

return layout;
}

#include "moc_stackedbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
