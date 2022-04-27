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

