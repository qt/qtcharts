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

#ifndef QHORIZONTALBARSERIES_H
#define QHORIZONTALBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QHorizontalBarSeriesPrivate;

class QT_CHARTS_EXPORT QHorizontalBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalBarSeries(QObject *parent = 0);
    ~QHorizontalBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QHorizontalBarSeries)
    Q_DISABLE_COPY(QHorizontalBarSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QHORIZONTALBARSERIES_H
