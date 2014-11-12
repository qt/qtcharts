/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/horizontalstackedbarchartitem_p.h>
#include <private/qabstractbarseries_p.h>
#include <private/qbarset_p.h>
#include <private/bar_p.h>

QT_CHARTS_BEGIN_NAMESPACE

HorizontalStackedBarChartItem::HorizontalStackedBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item)
    : AbstractBarChartItem(series, item)
{
}

void HorizontalStackedBarChartItem::initializeLayout()
{
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
    qreal barWidth = m_series->d_func()->barWidth();

    m_layout.clear();
    for(int category = 0; category < categoryCount; category++) {
        for (int set = 0; set < setCount; set++) {
            QRectF rect;
            QPointF topLeft;
            QPointF bottomRight;
            if (domain()->type() == AbstractDomain::LogXYDomain || domain()->type() == AbstractDomain::LogXLogYDomain) {
                topLeft = domain()->calculateGeometryPoint(QPointF(domain()->minX(), category - barWidth / 2), m_validData);
                bottomRight = domain()->calculateGeometryPoint(QPointF(domain()->minX(), category + barWidth / 2), m_validData);
            } else {
                topLeft = domain()->calculateGeometryPoint(QPointF(0, category - barWidth / 2), m_validData);
                bottomRight = domain()->calculateGeometryPoint(QPointF(0, category + barWidth / 2), m_validData);
            }

            if (!m_validData)
                 return;

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            m_layout.append(rect.normalized());
        }
    }
}

QVector<QRectF> HorizontalStackedBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accuracy
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
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
                bottomRight = domain()->calculateGeometryPoint(QPointF(value + negativeSum, category - barWidth / 2), m_validData);
                if (domain()->type() == AbstractDomain::LogXYDomain || domain()->type() == AbstractDomain::LogXLogYDomain)
                    topLeft = domain()->calculateGeometryPoint(QPointF(set ? negativeSum : domain()->minX(), category + barWidth / 2), m_validData);
                else
                    topLeft = domain()->calculateGeometryPoint(QPointF(set ? negativeSum : 0, category + barWidth / 2), m_validData);
                negativeSum += value;
            } else {
                bottomRight = domain()->calculateGeometryPoint(QPointF(value + positiveSum, category - barWidth / 2), m_validData);
                if (domain()->type() == AbstractDomain::LogXYDomain || domain()->type() == AbstractDomain::LogXLogYDomain)
                    topLeft = domain()->calculateGeometryPoint(QPointF(set ? positiveSum : domain()->minX(), category + barWidth / 2), m_validData);
                else
                    topLeft = domain()->calculateGeometryPoint(QPointF(set ? positiveSum : 0, category + barWidth / 2), m_validData);
                positiveSum += value;
            }

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect.normalized());
        }
    }
    return layout;
}

#include "moc_horizontalstackedbarchartitem_p.cpp"

QT_CHARTS_END_NAMESPACE

