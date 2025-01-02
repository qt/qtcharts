// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBARSERIES_H
#define QBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE

class QBarSeriesPrivate;

class Q_CHARTS_EXPORT QBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QBarSeries(QObject *parent = nullptr);
    ~QBarSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QBarSeries)
    Q_DISABLE_COPY(QBarSeries)
};

QT_END_NAMESPACE

#endif // QBARSERIES_H
