// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only


#ifndef QAREALEGENDMARKER_H
#define QAREALEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#if QT_CONFIG(charts_area_chart)
#include <QtCharts/QLegendMarker>
#include <QtCharts/QAreaSeries>

QT_BEGIN_NAMESPACE

class QAreaLegendMarkerPrivate;

class Q_CHARTS_EXPORT QAreaLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QAreaLegendMarker(QAreaSeries *series, QLegend *legend, QObject *parent = nullptr);
    virtual ~QAreaLegendMarker();

    LegendMarkerType type() override { return LegendMarkerTypeArea; }

    // Related series
    QAreaSeries* series() override;

protected:
    QAreaLegendMarker(QAreaLegendMarkerPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QAreaLegendMarker)
    Q_DISABLE_COPY(QAreaLegendMarker)

};

QT_END_NAMESPACE

#endif // QT_CONFIG(charts_area_chart)
#endif // QAREALEGENDMARKER_H
