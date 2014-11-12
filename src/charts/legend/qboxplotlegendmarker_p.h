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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBOXPLOTLEGENDMARKER_P_H
#define QBOXPLOTLEGENDMARKER_P_H

#include <QtCharts/QChartGlobal>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <QtCharts/QBoxPlotSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QBoxPlotLegendMarker;

class QBoxPlotLegendMarkerPrivate : public QLegendMarkerPrivate
{
    Q_OBJECT
public:
    explicit QBoxPlotLegendMarkerPrivate(QBoxPlotLegendMarker *q, QBoxPlotSeries *series, QLegend *legend);
    virtual ~QBoxPlotLegendMarkerPrivate();

    virtual QAbstractSeries *series();
    virtual QObject *relatedObject();

public Q_SLOTS:
    virtual void updated();

private:
    QBoxPlotLegendMarker *q_ptr;
    QBoxPlotSeries *m_series;

    Q_DECLARE_PUBLIC(QBoxPlotLegendMarker)
};

QT_CHARTS_END_NAMESPACE

#endif // QBOXPLOTLEGENDMARKER_P_H
