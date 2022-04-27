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

#ifndef QHORIZONTALPERCENTBARSERIES_H
#define QHORIZONTALPERCENTBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE

class QHorizontalPercentBarSeriesPrivate;

class Q_CHARTS_EXPORT QHorizontalPercentBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalPercentBarSeries(QObject *parent = nullptr);
    ~QHorizontalPercentBarSeries();
    QAbstractSeries::SeriesType type() const override;

private:
    Q_DECLARE_PRIVATE(QHorizontalPercentBarSeries)
    Q_DISABLE_COPY(QHorizontalPercentBarSeries)
};

QT_END_NAMESPACE

#endif // QHORIZONTALPERCENTBARSERIES_H
