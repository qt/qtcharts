/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "horizontalstackedbarchartitem_p.h"
#include "qabstractbarseries_p.h"
#include "qbarset_p.h"
#include "bar_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

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
            if (!m_validData)
                 return QVector<QRectF>();
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect.normalized());
        }
    }
    return layout;
}

#include "moc_horizontalstackedbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

