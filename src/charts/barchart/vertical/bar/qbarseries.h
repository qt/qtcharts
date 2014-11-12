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

#ifndef QBARSERIES_H
#define QBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QBarSeriesPrivate;

class QT_CHARTS_EXPORT QBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QBarSeries(QObject *parent = 0);
    ~QBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QBarSeries)
    Q_DISABLE_COPY(QBarSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QBARSERIES_H
