/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <private/barchartitem_p.h>
#include <private/bar_p.h>
#include <private/qabstractbarseries_p.h>
#include <QtCharts/QBarSet>
#include <private/qbarset_p.h>

QT_CHARTS_BEGIN_NAMESPACE

BarChartItem::BarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    AbstractBarChartItem(series, item)
{
    m_orientation = Qt::Vertical;
    connect(series, SIGNAL(labelsPositionChanged(QAbstractBarSeries::LabelsPosition)),
            this, SLOT(handleLabelsPositionChanged()));
    connect(series, SIGNAL(labelsFormatChanged(QString)), this, SLOT(positionLabels()));
}

void BarChartItem::initializeLayout(int set, int category, int layoutIndex, bool resetAnimation)
{
    QRectF rect;

    int previousSetIndex = layoutIndex - m_categoryCount;
    if (previousSetIndex >= 0) {
        rect = m_layout.at(previousSetIndex);
        qreal oldRight = rect.right();
        if (resetAnimation)
            rect.setRight(oldRight + rect.width());
        rect.setLeft(oldRight);
        rect.setTop(rect.bottom());
    } else {
        QPointF topLeft;
        QPointF bottomRight;
        qreal setCount = m_series->count();
        qreal barWidth = m_series->d_func()->barWidth();
        if (domain()->type() == AbstractDomain::XLogYDomain
                || domain()->type() == AbstractDomain::LogXLogYDomain) {
            topLeft = domain()->calculateGeometryPoint(
                        QPointF(category - barWidth / 2 + set/setCount * barWidth,
                                domain()->minY()), m_validData);
            bottomRight = domain()->calculateGeometryPoint(
                        QPointF(category - barWidth / 2 + (set + 1)/setCount * barWidth,
                                domain()->minY()), m_validData);
        } else {
            topLeft = domain()->calculateGeometryPoint(
                        QPointF(category - barWidth / 2 + set/setCount * barWidth, 0), m_validData);
            bottomRight = domain()->calculateGeometryPoint(
                        QPointF(category - barWidth / 2 + (set + 1)/setCount * barWidth, 0),
                        m_validData);
        }

        if (m_validData) {
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
        }
    }
    m_layout[layoutIndex] = rect.normalized();
}

QVector<QRectF> BarChartItem::calculateLayout()
{
    QVector<QRectF> layout;
    layout.reserve(m_layout.size());

    // Use temporary qreals for accuracy
    qreal setCount = m_series->count();
    qreal barWidth = m_series->d_func()->barWidth();

    for (int set = 0; set < setCount; set++) {
        QBarSet *barSet = m_series->barSets().at(set);
        const QList<Bar *> bars = m_barMap.value(barSet);
        for (int c = 0; c < m_categoryCount; c++) {
            int category = bars.at(c)->index();
            qreal value = barSet->at(category);
            QRectF rect;
            QPointF topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set)/(setCount) * barWidth, value), m_validData);
            QPointF bottomRight;
            if (domain()->type() == AbstractDomain::XLogYDomain || domain()->type() == AbstractDomain::LogXLogYDomain)
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set + 1)/(setCount) * barWidth, domain()->minY()), m_validData);
            else
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set + 1)/(setCount) * barWidth, 0), m_validData);

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect.normalized());
        }
    }

    return layout;
}

void BarChartItem::handleLabelsPositionChanged()
{
    positionLabels();
}

void BarChartItem::positionLabels()
{
    positionLabelsVertical();
}

#include "moc_barchartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
