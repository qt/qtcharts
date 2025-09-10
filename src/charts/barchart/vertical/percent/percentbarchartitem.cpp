// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/percentbarchartitem_p.h>
#include <private/bar_p.h>
#include <private/qabstractbarseries_p.h>
#include <QtCharts/QBarSet>
#include <private/qbarset_p.h>

QT_BEGIN_NAMESPACE

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

void PercentBarChartItem::initializeLayout(int set, int category,
                                           int layoutIndex, bool resetAnimation)
{
    Q_UNUSED(set);
    Q_UNUSED(resetAnimation);

    QRectF rect;

    if (set > 0) {
        QBarSet *barSet = m_series->barSets().at(set - 1);
        Bar *bar = m_indexForBarMap.value(barSet).value(category);
        rect = m_layout.at(bar->layoutIndex());
        rect.setBottom(rect.top());
    } else {
        QPointF topLeft;
        QPointF bottomRight;
        const qreal barWidth = m_series->d_func()->barWidth() * m_seriesWidth;
        if (domain()->type() == AbstractDomain::XLogYDomain
                || domain()->type() == AbstractDomain::LogXLogYDomain) {
            topLeft = topLeftPoint(category, barWidth, domain()->minY());
            bottomRight = bottomRightPoint(category, barWidth, domain()->minY());
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

void PercentBarChartItem::markLabelsDirty(QBarSet *barset, int index, int count)
{
    Q_UNUSED(barset);
    // Percent series need to dirty all labels of the stack
    QList<QBarSet *> sets = m_barMap.keys();
    for (int set = 0; set < sets.size(); set++)
        AbstractBarChartItem::markLabelsDirty(sets.at(set), index, count);
}

QPointF PercentBarChartItem::topLeftPoint(int category, qreal barWidth, qreal value)
{
    return domain()->calculateGeometryPoint(
                QPointF(m_seriesPosAdjustment + category - (barWidth / 2.0), value), m_validData);
}

QPointF PercentBarChartItem::bottomRightPoint(int category, qreal barWidth, qreal value)
{
    return domain()->calculateGeometryPoint(
                QPointF(m_seriesPosAdjustment + category + (barWidth / 2.0), value), m_validData);
}

QList<QRectF> PercentBarChartItem::calculateLayout()
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
            qreal topY = 0.0;
            qreal newSum = value + sum;
            qreal bottomY = 0.0;
            if (categorySum != 0.0) {
                if (newSum > 0.0)
                    topY = 100.0 * newSum / categorySum;
                if (sum > 0.0)
                    bottomY = 100.0 * sum / categorySum;
            }
            QPointF topLeft = topLeftPoint(category, barWidth, topY);
            QPointF bottomRight;
            if (domain()->type() == AbstractDomain::XLogYDomain
                    || domain()->type() == AbstractDomain::LogXLogYDomain) {
                bottomRight = bottomRightPoint(category, barWidth,
                                               set ? bottomY : domain()->minY());
            } else {
                bottomRight = bottomRightPoint(category, barWidth, bottomY);
            }

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout[bar->layoutIndex()] = rect.normalized();
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

QT_END_NAMESPACE

#include "moc_percentbarchartitem_p.cpp"
