/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/qlineseries.h>
#include <QtCore/QList>
#include <QtCore/QPointF>
#include <QtCore/QtGlobal>

QT_CHARTS_BEGIN_NAMESPACE

class QSplineSeriesPrivate;

class QT_CHARTS_EXPORT QSplineSeries : public QLineSeries
{
    Q_OBJECT

public:
    explicit QSplineSeries(QObject *parent = 0);
    ~QSplineSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QSplineSeries)
    Q_DISABLE_COPY(QSplineSeries)
    friend class SplineChartItem;
};

QT_CHARTS_END_NAMESPACE

#endif // QSPLINESERIES_H
