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

#include "percentbarchartitem_p.h"
#include "bar_p.h"
#include "qabstractbarseries_p.h"
#include "qbarset.h"
#include "qbarset_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PercentBarChartItem::PercentBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    AbstractBarChartItem(series, item)
{
}

void PercentBarChartItem::initializeLayout()
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

            if (domain()->type() == AbstractDomain::XLogYDomain || domain()->type() == AbstractDomain::LogXLogYDomain) {
                topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2, domain()->minY()), m_validData);
                bottomRight = domain()->calculateGeometryPoint(QPointF(category + barWidth / 2, domain()->minY()), m_validData);
            } else {
                topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2, 0), m_validData);
                bottomRight = domain()->calculateGeometryPoint(QPointF(category + barWidth / 2, 0), m_validData);
            }

            if (!m_validData)
                 return;

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            m_layout.append(rect.normalized());
        }
    }
}

QVector<QRectF> PercentBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accuracy
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
    qreal barWidth = m_series->d_func()->barWidth();

    for(int category = 0; category < categoryCount; category++) {
        qreal sum = 0;
        qreal categorySum = m_series->d_func()->categorySum(category);
        for (int set = 0; set < setCount; set++) {
            qreal value = m_series->barSets().at(set)->at(category);
            QRectF rect;
            QPointF topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth/2, 100 * (value + sum)/categorySum), m_validData);
            QPointF bottomRight;
            if (domain()->type() == AbstractDomain::XLogYDomain || domain()->type() == AbstractDomain::LogXLogYDomain)
                bottomRight = domain()->calculateGeometryPoint(QPointF(category + barWidth/2, set ? 100 * sum/categorySum : domain()->minY()), m_validData);
            else
                bottomRight = domain()->calculateGeometryPoint(QPointF(category + barWidth/2, set ? 100 * sum/categorySum : 0), m_validData);

            if (!m_validData)
                 return QVector<QRectF>();
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect.normalized());
            sum +=value;
        }
    }
    return layout;
}

void PercentBarChartItem::handleUpdatedBars()
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
            int p = m_series->d_func()->percentageAt(set, category) * 100;
            QString vString(QString::number(p));
            vString.truncate(3);
            vString.append("%");
            label->setText(vString);
            label->setFont(barSet->m_labelFont);
            label->setBrush(barSet->m_labelBrush);
            label->update();
            itemIndex++;
        }
    }
}

#include "moc_percentbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
