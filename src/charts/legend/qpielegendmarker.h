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

#ifndef QPIELEGENDMARKER_H
#define QPIELEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_BEGIN_NAMESPACE

class QPieLegendMarkerPrivate;

class Q_CHARTS_EXPORT QPieLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QPieLegendMarker(QPieSeries *series, QPieSlice *slice, QLegend *legend, QObject *parent = nullptr);
    virtual ~QPieLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypePie; }

    // Related series and slice
    virtual QPieSeries* series();
    QPieSlice* slice();

protected:
    QPieLegendMarker(QPieLegendMarkerPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QPieLegendMarker)
    Q_DISABLE_COPY(QPieLegendMarker)

};

QT_CHARTS_END_NAMESPACE
#endif // QPIELEGENDMARKER_H
