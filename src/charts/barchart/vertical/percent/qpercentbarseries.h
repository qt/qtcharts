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

#ifndef QPERCENTBARSERIES_H
#define QPERCENTBARSERIES_H

#include <QtCore/QStringList>
#include <QtCharts/QAbstractBarSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QPercentBarSeriesPrivate;

class QT_CHARTS_EXPORT QPercentBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QPercentBarSeries(QObject *parent = 0);
    ~QPercentBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QPercentBarSeries)
    Q_DISABLE_COPY(QPercentBarSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QPERCENTBARSERIES_H
