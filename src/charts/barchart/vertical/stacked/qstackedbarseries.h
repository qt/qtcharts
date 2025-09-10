// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QSTACKEDBARSERIES_H
#define QSTACKEDBARSERIES_H

#include <QtCore/QStringList>
#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE

class QStackedBarSeriesPrivate;

class Q_CHARTS_EXPORT QStackedBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QStackedBarSeries(QObject *parent = nullptr);
    ~QStackedBarSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QStackedBarSeries)
    Q_DISABLE_COPY(QStackedBarSeries)
};

QT_END_NAMESPACE

#endif // QSTACKEDBARSERIES_H
