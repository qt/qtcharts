// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only


#ifndef QLINESERIES_H
#define QLINESERIES_H
#include <QtCharts/QChartGlobal>
#if QT_CONFIG(charts_line_chart)
#include <QtCharts/QXYSeries>
#include <QtGui/QPen>

QT_BEGIN_NAMESPACE

class QLineSeriesPrivate;

class Q_CHARTS_EXPORT QLineSeries : public QXYSeries
{
    Q_OBJECT

public:
    explicit QLineSeries(QObject *parent = nullptr);
    ~QLineSeries();
    QAbstractSeries::SeriesType type() const override;

protected:
    QLineSeries(QLineSeriesPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QLineSeries)
    Q_DISABLE_COPY(QLineSeries)
    friend class LineChartItem;
};

QT_END_NAMESPACE

#endif // QT_CONFIG(charts_line_chart)
#endif // QLINESERIES_H
