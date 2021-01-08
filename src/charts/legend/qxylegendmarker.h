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

#ifndef QXYLEGENDMARKER_H
#define QXYLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QXYSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QXYLegendMarkerPrivate;

class Q_CHARTS_EXPORT QXYLegendMarker : public QLegendMarker
{
    Q_OBJECT
public:
    explicit QXYLegendMarker(QXYSeries *series, QLegend *legend, QObject *parent = nullptr);
    virtual ~QXYLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypeXY; }

    // Related series
    virtual QXYSeries* series();

protected:
    QXYLegendMarker(QXYLegendMarkerPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QXYLegendMarker)
    Q_DISABLE_COPY(QXYLegendMarker)

};

QT_CHARTS_END_NAMESPACE

#endif // QXYLEGENDMARKER_H
