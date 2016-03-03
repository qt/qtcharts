/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/
#ifndef QBARLEGENDMARKER_H
#define QBARLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QBarSet>

QT_CHARTS_BEGIN_NAMESPACE

class QLegend;
class QBarLegendMarkerPrivate;

class QT_CHARTS_EXPORT QBarLegendMarker : public QLegendMarker
{
    Q_OBJECT
public:
    explicit QBarLegendMarker(QAbstractBarSeries *series, QBarSet *barset, QLegend *legend, QObject *parent = Q_NULLPTR);
    virtual ~QBarLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypeBar; }

    // Related series and barset
    virtual QAbstractBarSeries* series();
    QBarSet* barset();

protected:
    QBarLegendMarker(QBarLegendMarkerPrivate &d, QObject *parent = Q_NULLPTR);

private:
    Q_DECLARE_PRIVATE(QBarLegendMarker)
    Q_DISABLE_COPY(QBarLegendMarker)

};

QT_CHARTS_END_NAMESPACE

#endif // QBARLEGENDMARKER_H
