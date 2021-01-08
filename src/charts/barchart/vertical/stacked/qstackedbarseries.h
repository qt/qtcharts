/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef QSTACKEDBARSERIES_H
#define QSTACKEDBARSERIES_H

#include <QtCore/QStringList>
#include <QtCharts/QAbstractBarSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QStackedBarSeriesPrivate;

class Q_CHARTS_EXPORT QStackedBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QStackedBarSeries(QObject *parent = nullptr);
    ~QStackedBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QStackedBarSeries)
    Q_DISABLE_COPY(QStackedBarSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QSTACKEDBARSERIES_H
