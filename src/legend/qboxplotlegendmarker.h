/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
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

#include <QChartGlobal>
#include <QLegendMarker>
#include <QBoxPlotSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBoxPlotLegendMarkerPrivate;

class QTCOMMERCIALCHART_EXPORT QBoxPlotLegendMarker : public QLegendMarker
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

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBOXPLOTLEGENDMARKER_H
