/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QBOXPLOTLEGENDMARKER_H
#define QBOXPLOTLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QBoxPlotSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QBoxPlotLegendMarkerPrivate;

class QT_CHARTS_EXPORT QBoxPlotLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QBoxPlotLegendMarker(QBoxPlotSeries *series, QLegend *legend, QObject *parent = 0);
    virtual ~QBoxPlotLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypeBoxPlot; }

    // Related series
    virtual QBoxPlotSeries* series();

protected:
    QBoxPlotLegendMarker(QBoxPlotLegendMarkerPrivate &d, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QBoxPlotLegendMarker)
    Q_DISABLE_COPY(QBoxPlotLegendMarker)
};

QT_CHARTS_END_NAMESPACE

#endif // QBOXPLOTLEGENDMARKER_H
