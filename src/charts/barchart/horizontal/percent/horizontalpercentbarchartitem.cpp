// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/horizontalpercentbarchartitem_p.h>
#include <private/qabstractbarseries_p.h>
#include <private/qbarset_p.h>
#include <private/bar_p.h>

QT_BEGIN_NAMESPACE

HorizontalPercentBarChartItem::HorizontalPercentBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item)
    : AbstractBarChartItem(series, item)
{
}

QString HorizontalPercentBarChartItem::generateLabelText(int set, int category, qreal value)
{
    Q_UNUSED(value);

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

void HorizontalPercentBarChartItem::initializeLayout(int set, int category,
                                                     int layoutIndex, bool resetAnimation)
{
    Q_UNUSED(set);
    Q_UNUSED(resetAnimation);

    QRectF rect;

    if (set > 0) {
        QBarSet *barSet = m_series->barSets().at(set - 1);
        Bar *bar = m_indexForBarMap.value(barSet).value(category);
        rect = m_layout.at(bar->layoutIndex());
        rect.setLeft(rect.right());
    } else {
        QPointF topLeft;
        QPointF bottomRight;
        const qreal barWidth = m_series->d_func()->barWidth() * m_seriesWidth;
        if (domain()->type() == AbstractDomain::LogXYDomain
                || domain()->type() == AbstractDomain::LogXLogYDomain) {
            topLeft = topLeftPoint(category, barWidth, domain()->minX());
            bottomRight = bottomRightPoint(category, barWidth, domain()->minX());
        } else {
            topLeft = topLeftPoint(category, barWidth, 0.0);
            bottomRight = bottomRightPoint(category, barWidth, 0.0);
        }
        if (m_validData) {
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
        }
    }
    m_layout[layoutIndex] = rect.normalized();
}

void HorizontalPercentBarChartItem::markLabelsDirty(QBarSet *barset, int index, int count)
{
    Q_UNUSED(barset);
    // Percent series need to dirty all labels of the stack
    QList<QBarSet *> sets = m_barMap.keys();
    for (int set = 0; set < sets.size(); set++)
        AbstractBarChartItem::markLabelsDirty(sets.at(set), index, count);
}

QPointF HorizontalPercentBarChartItem::topLeftPoint(int category, qreal barWidth, qreal value)
{
    return domain()->calculateGeometryPoint(
                QPointF(value, m_seriesPosAdjustment + category - (barWidth / 2.0)), m_validData);
}

QPointF HorizontalPercentBarChartItem::bottomRightPoint(int category, qreal barWidth, qreal value)
{
    return domain()->calculateGeometryPoint(
                QPointF(value, m_seriesPosAdjustment + category + (barWidth / 2.0)), m_validData);
}

QList<QRectF> HorizontalPercentBarChartItem::calculateLayout()
{
    QList<QRectF> layout;
    layout.resize(m_layout.size());

    const int setCount = m_series->count();
    const qreal barWidth = m_series->d_func()->barWidth() * m_seriesWidth;

    QList<qreal> categorySums(m_categoryCount);
    QList<qreal> tempSums(m_categoryCount, 0.0);

    for (int category = 0; category < m_categoryCount; category++)
        categorySums[category] = m_series->d_func()->categorySum(category + m_firstCategory);

    for (int set = 0; set < setCount; set++) {
        QBarSet *barSet = m_series->barSets().at(set);
        const QList<Bar *> bars = m_barMap.value(barSet);
        for (int i = 0; i < m_categoryCount; i++) {
            Bar *bar = bars.at(i);
            const int category = bar->index();
            qreal &sum = tempSums[category - m_firstCategory];
            const qreal &categorySum = categorySums.at(category - m_firstCategory);
            qreal value = barSet->at(category);
            QRectF rect;
            qreal topX = 0.0;
            qreal bottomX = 0.0;
            qreal newSum = value + sum;
            if (categorySum != 0.0) {
                if (sum > 0.0)
                    topX = 100.0 * sum / categorySum;
                if (newSum > 0.0)
                    bottomX = 100.0 * newSum / categorySum;
            }
            QPointF topLeft;
            if (domain()->type() == AbstractDomain::LogXYDomain
                    || domain()->type() == AbstractDomain::LogXLogYDomain) {
                topLeft = topLeftPoint(category, barWidth, set ? topX : domain()->minX());
            } else {
                topLeft = topLeftPoint(category, barWidth, set ? topX : 0.0);
            }
            QPointF bottomRight = bottomRightPoint(category, barWidth, bottomX);

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout[bar->layoutIndex()] = rect.normalized();
            sum = newSum;
        }
    }
    return layout;
}

QT_END_NAMESPACE

#include "moc_horizontalpercentbarchartitem_p.cpp"
