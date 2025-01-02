// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H
#include <QtCharts/QChartGlobal>
#if QT_CONFIG(charts_spline_chart)
#include <QtCharts/qlineseries.h>
#include <QtCore/QList>
#include <QtCore/QPointF>

QT_BEGIN_NAMESPACE

class QSplineSeriesPrivate;

class Q_CHARTS_EXPORT QSplineSeries : public QLineSeries
{
    Q_OBJECT

public:
    explicit QSplineSeries(QObject *parent = nullptr);
    ~QSplineSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QSplineSeries)
    Q_DISABLE_COPY(QSplineSeries)
    friend class SplineChartItem;
};

QT_END_NAMESPACE

#endif // QT_CONFIG(charts_spline_chart)
#endif // QSPLINESERIES_H

