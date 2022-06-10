// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#ifndef QBARLEGENDMARKER_H
#define QBARLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QBarSet>

QT_BEGIN_NAMESPACE

class QLegend;
class QBarLegendMarkerPrivate;

class Q_CHARTS_EXPORT QBarLegendMarker : public QLegendMarker
{
    Q_OBJECT
public:
    explicit QBarLegendMarker(QAbstractBarSeries *series, QBarSet *barset, QLegend *legend, QObject *parent = nullptr);
    virtual ~QBarLegendMarker();

    LegendMarkerType type() override { return LegendMarkerTypeBar; }

    // Related series and barset
    QAbstractBarSeries* series() override;
    QBarSet* barset();

protected:
    QBarLegendMarker(QBarLegendMarkerPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QBarLegendMarker)
    Q_DISABLE_COPY(QBarLegendMarker)

};

QT_END_NAMESPACE

#endif // QBARLEGENDMARKER_H
