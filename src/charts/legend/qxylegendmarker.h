// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QXYLEGENDMARKER_H
#define QXYLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QXYSeries>

QT_BEGIN_NAMESPACE

class QXYLegendMarkerPrivate;

class Q_CHARTS_EXPORT QXYLegendMarker : public QLegendMarker
{
    Q_OBJECT
public:
    explicit QXYLegendMarker(QXYSeries *series, QLegend *legend, QObject *parent = nullptr);
    virtual ~QXYLegendMarker();

    LegendMarkerType type() override { return LegendMarkerTypeXY; }

    // Related series
    QXYSeries* series() override;

protected:
    QXYLegendMarker(QXYLegendMarkerPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QXYLegendMarker)
    Q_DISABLE_COPY(QXYLegendMarker)

};

QT_END_NAMESPACE

#endif // QXYLEGENDMARKER_H
