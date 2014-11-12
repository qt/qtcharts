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

#ifndef QSTACKEDBARSERIES_H
#define QSTACKEDBARSERIES_H

#include <QtCore/QStringList>
#include <QtCharts/QAbstractBarSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QStackedBarSeriesPrivate;

class QT_CHARTS_EXPORT QStackedBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QStackedBarSeries(QObject *parent = 0);
    ~QStackedBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QStackedBarSeries)
    Q_DISABLE_COPY(QStackedBarSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QSTACKEDBARSERIES_H
