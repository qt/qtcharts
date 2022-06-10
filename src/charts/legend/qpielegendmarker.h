// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QPIELEGENDMARKER_H
#define QPIELEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_BEGIN_NAMESPACE

class QPieLegendMarkerPrivate;

class Q_CHARTS_EXPORT QPieLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QPieLegendMarker(QPieSeries *series, QPieSlice *slice, QLegend *legend, QObject *parent = nullptr);
    virtual ~QPieLegendMarker();

    LegendMarkerType type() override { return LegendMarkerTypePie; }

    // Related series and slice
    QPieSeries* series() override;
    QPieSlice* slice();

protected:
    QPieLegendMarker(QPieLegendMarkerPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QPieLegendMarker)
    Q_DISABLE_COPY(QPieLegendMarker)

};

QT_END_NAMESPACE
#endif // QPIELEGENDMARKER_H
