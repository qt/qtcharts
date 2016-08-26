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

#include <private/horizontalpercentbarchartitem_p.h>
#include <private/qabstractbarseries_p.h>
#include <private/qbarset_p.h>
#include <private/bar_p.h>

QT_CHARTS_BEGIN_NAMESPACE

HorizontalPercentBarChartItem::HorizontalPercentBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item)
    : AbstractBarChartItem(series, item)
{
}

QString HorizontalPercentBarChartItem::generateLabelText(int set, int category, qreal value)
{
    Q_UNUSED(value)

    static const QString valueTag(QLatin1String("@value"));
    qreal p = m_series->d_func()->percentageAt(set, category) * 100.0;
    QString vString(presenter()->numberToString(p, 'f', 0));
    QString valueLabel;
    if (m_series->labelsFormat().isEmpty()) {
        vString.append(QStringLiteral("%"));
        valueLabel = vString;
    } else {
        valueLabel = m_series->labelsFormat();
        valueLabel.replace(valueTag, vString);
    }

    return valueLabel;
}

void HorizontalPercentBarChartItem::initializeLayout(int set, int category, int layoutIndex,
                                                     bool resetAnimation)
{
    Q_UNUSED(set)
    Q_UNUSED(resetAnimation)

    QRectF rect;

    int previousSetIndex = layoutIndex - m_categoryCount;
    if (previousSetIndex >= 0) {
        rect = m_layout.at(previousSetIndex);
        rect.setLeft(rect.right());
    } else {
        QPointF topLeft;
        QPointF bottomRight;
        qreal barWidth = m_series->d_func()->barWidth();
        if (domain()->type() == AbstractDomain::LogXYDomain
                || domain()->type() == AbstractDomain::LogXLogYDomain) {
            topLeft = domain()->calculateGeometryPoint(
                        QPointF(domain()->minX(), category - barWidth / 2), m_validData);
            bottomRight = domain()->calculateGeometryPoint(
                        QPointF(domain()->minX(), category + barWidth / 2), m_validData);
        } else {
            topLeft = domain()->calculateGeometryPoint(
                        QPointF(0, category - barWidth / 2), m_validData);
            bottomRight = domain()->calculateGeometryPoint(
                        QPointF(0, category + barWidth / 2), m_validData);
        }
        if (m_validData) {
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
        }
    }
    m_layout[layoutIndex] = rect.normalized();
}

void HorizontalPercentBarChartItem::markLabelsDirty(QBarSet *barset, int visualIndex, int count)
{
    Q_UNUSED(barset)
    // Percent series need to dirty all labels of the stack
    QList<QBarSet *> sets = m_barMap.keys();
    for (int set = 0; set < sets.size(); set++)
        AbstractBarChartItem::markLabelsDirty(sets.at(set), visualIndex, count);
}

QVector<QRectF> HorizontalPercentBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;
    layout.reserve(m_layout.size());

    // Use temporary qreals for accuracy
    qreal setCount = m_series->count();
    qreal barWidth = m_series->d_func()->barWidth();

    QVector<qreal> categorySums(m_categoryCount);
    QVector<qreal> tempSums(m_categoryCount, 0.0);
    for (int category = 0; category < m_categoryCount; category++)
        categorySums[category] = m_series->d_func()->categorySum(category + m_firstCategory);
    for (int set = 0; set < setCount; set++) {
        const QBarSet *barSet = m_series->barSets().at(set);
        for (int category = m_firstCategory; category <= m_lastCategory; category++) {
            qreal &sum = tempSums[category - m_firstCategory];
            const qreal &categorySum = categorySums.at(category - m_firstCategory);
            qreal value = barSet->at(category);
            QRectF rect;
            qreal topX = 0;
            if (sum > 0)
                topX = 100 * sum / categorySum;
            qreal bottomX = 0;
            qreal newSum = value + sum;
            if (newSum > 0)
                bottomX = 100 * newSum / categorySum;
            QPointF topLeft;
            if (domain()->type() == AbstractDomain::LogXYDomain || domain()->type() == AbstractDomain::LogXLogYDomain)
                topLeft = domain()->calculateGeometryPoint(QPointF(set ? topX : domain()->minX(), category - barWidth/2), m_validData);
            else
                topLeft = domain()->calculateGeometryPoint(QPointF(set ? topX : 0, category - barWidth/2), m_validData);
            QPointF bottomRight = domain()->calculateGeometryPoint(QPointF(bottomX, category + barWidth/2), m_validData);

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect.normalized());
            sum = newSum;
        }
    }
    return layout;
}

#include "moc_horizontalpercentbarchartitem_p.cpp"

QT_CHARTS_END_NAMESPACE

