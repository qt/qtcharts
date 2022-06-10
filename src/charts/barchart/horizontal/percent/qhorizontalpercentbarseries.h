// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QHORIZONTALPERCENTBARSERIES_H
#define QHORIZONTALPERCENTBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE

class QHorizontalPercentBarSeriesPrivate;

class Q_CHARTS_EXPORT QHorizontalPercentBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalPercentBarSeries(QObject *parent = nullptr);
    ~QHorizontalPercentBarSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QHorizontalPercentBarSeries)
    Q_DISABLE_COPY(QHorizontalPercentBarSeries)
};

QT_END_NAMESPACE

#endif // QHORIZONTALPERCENTBARSERIES_H
