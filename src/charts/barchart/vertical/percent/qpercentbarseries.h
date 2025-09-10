// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QPERCENTBARSERIES_H
#define QPERCENTBARSERIES_H

#include <QtCore/QStringList>
#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE

class QPercentBarSeriesPrivate;

class Q_CHARTS_EXPORT QPercentBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QPercentBarSeries(QObject *parent = nullptr);
    ~QPercentBarSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QPercentBarSeries)
    Q_DISABLE_COPY(QPercentBarSeries)
};

QT_END_NAMESPACE

#endif // QPERCENTBARSERIES_H
