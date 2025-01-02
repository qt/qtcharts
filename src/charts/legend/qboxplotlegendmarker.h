// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBOXPLOTLEGENDMARKER_H
#define QBOXPLOTLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QBoxPlotSeries>

QT_BEGIN_NAMESPACE

class QBoxPlotLegendMarkerPrivate;

class Q_CHARTS_EXPORT QBoxPlotLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QBoxPlotLegendMarker(QBoxPlotSeries *series, QLegend *legend, QObject *parent = nullptr);
    virtual ~QBoxPlotLegendMarker();

    LegendMarkerType type() override { return LegendMarkerTypeBoxPlot; }

    // Related series
    QBoxPlotSeries* series() override;

protected:
    QBoxPlotLegendMarker(QBoxPlotLegendMarkerPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QBoxPlotLegendMarker)
    Q_DISABLE_COPY(QBoxPlotLegendMarker)
};

QT_END_NAMESPACE

#endif // QBOXPLOTLEGENDMARKER_H
