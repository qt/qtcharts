// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QHORIZONTALSTACKEDBARSERIES_H
#define QHORIZONTALSTACKEDBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE

class QHorizontalStackedBarSeriesPrivate;

class Q_CHARTS_EXPORT QHorizontalStackedBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalStackedBarSeries(QObject *parent = nullptr);
    ~QHorizontalStackedBarSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QHorizontalStackedBarSeries)
    Q_DISABLE_COPY(QHorizontalStackedBarSeries)
};

QT_END_NAMESPACE

#endif // QHORIZONTALSTACKEDBARSERIES_H
