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

#include <private/percentbarchartitem_p.h>
#include <private/bar_p.h>
#include <private/qabstractbarseries_p.h>
#include <QtCharts/QBarSet>
#include <private/qbarset_p.h>

QT_CHARTS_BEGIN_NAMESPACE

PercentBarChartItem::PercentBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    AbstractBarChartItem(series, item)
{
    m_orientation = Qt::Vertical;
    connect(series, SIGNAL(labelsPositionChanged(QAbstractBarSeries::LabelsPosition)),
            this, SLOT(handleLabelsPositionChanged()));
    connect(series, SIGNAL(labelsFormatChanged(QString)), this, SLOT(positionLabels()));
}

QString PercentBarChartItem::generateLabelText(int set, int category, qreal value)
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

void PercentBarChartItem::initializeLayout(int set, int category, int layoutIndex,
                                           bool resetAnimation)
{
    Q_UNUSED(set)
    Q_UNUSED(resetAnimation)

    QRectF rect;

    int previousSetIndex = layoutIndex - m_categoryCount;
    if (previousSetIndex >= 0) {
        rect = m_layout.at(previousSetIndex);
        rect.setBottom(rect.top());
    } else {
        QPointF topLeft;
        QPointF bottomRight;
        qreal barWidth = m_series->d_func()->barWidth();
        if (domain()->type() == AbstractDomain::XLogYDomain
                || domain()->type() == AbstractDomain::LogXLogYDomain) {
            topLeft = domain()->calculateGeometryPoint(
                        QPointF(category - barWidth / 2, domain()->minY()), m_validData);
            bottomRight = domain()->calculateGeometryPoint(
                        QPointF(category + barWidth / 2, domain()->minY()), m_validData);
        } else {
            topLeft = domain()->calculateGeometryPoint(
                        QPointF(category - barWidth / 2, 0), m_validData);
            bottomRight = domain()->calculateGeometryPoint(
                        QPointF(category + barWidth / 2, 0), m_validData);
        }
        if (m_validData) {
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
        }
    }

    m_layout[layoutIndex] = rect.normalized();
}

void PercentBarChartItem::markLabelsDirty(QBarSet *barset, int visualIndex, int count)
{
    Q_UNUSED(barset)
    // Percent series need to dirty all labels of the stack
    QList<QBarSet *> sets = m_barMap.keys();
    for (int set = 0; set < sets.size(); set++)
        AbstractBarChartItem::markLabelsDirty(sets.at(set), visualIndex, count);
}

QVector<QRectF> PercentBarChartItem::calculateLayout()
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
            qreal topY = 0;
            qreal newSum = value + sum;
            if (newSum > 0)
                topY = 100 * newSum / categorySum;
            qreal bottomY = 0;
            if (sum > 0)
                bottomY = 100 * sum / categorySum;
            QPointF topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth/2, topY), m_validData);
            QPointF bottomRight;
            if (domain()->type() == AbstractDomain::XLogYDomain || domain()->type() == AbstractDomain::LogXLogYDomain)
                bottomRight = domain()->calculateGeometryPoint(QPointF(category + barWidth/2, set ? bottomY : domain()->minY()), m_validData);
            else
                bottomRight = domain()->calculateGeometryPoint(QPointF(category + barWidth/2, set ? bottomY : 0), m_validData);

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect.normalized());
            sum = newSum;
        }
    }
    return layout;
}

void PercentBarChartItem::handleLabelsPositionChanged()
{
    positionLabels();
}

void PercentBarChartItem::positionLabels()
{
    positionLabelsVertical();
}

#include "moc_percentbarchartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
