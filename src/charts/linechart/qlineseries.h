/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/


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
