// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QHORIZONTALBARSERIES_H
#define QHORIZONTALBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE

class QHorizontalBarSeriesPrivate;

class Q_CHARTS_EXPORT QHorizontalBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalBarSeries(QObject *parent = nullptr);
    ~QHorizontalBarSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QHorizontalBarSeries)
    Q_DISABLE_COPY(QHorizontalBarSeries)
};

QT_END_NAMESPACE

#endif // QHORIZONTALBARSERIES_H
