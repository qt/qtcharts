/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QHORIZONTALPERCENTBARSERIES_H
#define QHORIZONTALPERCENTBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QHorizontalPercentBarSeriesPrivate;

class QT_CHARTS_EXPORT QHorizontalPercentBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalPercentBarSeries(QObject *parent = 0);
    ~QHorizontalPercentBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QHorizontalPercentBarSeries)
    Q_DISABLE_COPY(QHorizontalPercentBarSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QHORIZONTALPERCENTBARSERIES_H
