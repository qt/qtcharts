/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef QLINESERIES_H
#define QLINESERIES_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QXYSeries>
#include <QtGui/QPen>

QT_CHARTS_BEGIN_NAMESPACE

class QLineSeriesPrivate;

class QT_CHARTS_EXPORT QLineSeries : public QXYSeries
{
    Q_OBJECT

public:
    explicit QLineSeries(QObject *parent = Q_NULLPTR);
    ~QLineSeries();
    QAbstractSeries::SeriesType type() const;

protected:
    QLineSeries(QLineSeriesPrivate &d, QObject *parent = Q_NULLPTR);

private:
    Q_DECLARE_PRIVATE(QLineSeries)
    Q_DISABLE_COPY(QLineSeries)
    friend class LineChartItem;
};

QT_CHARTS_END_NAMESPACE

#endif // QLINESERIES_H
