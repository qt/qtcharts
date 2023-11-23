// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
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
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QBoxPlotLegendMarker;

class Q_CHARTS_EXPORT QBoxPlotLegendMarkerPrivate : public QLegendMarkerPrivate
{
    Q_OBJECT
public:
    explicit QBoxPlotLegendMarkerPrivate(QBoxPlotLegendMarker *q, QBoxPlotSeries *series, QLegend *legend);
    virtual ~QBoxPlotLegendMarkerPrivate();

    QAbstractSeries *series() override;
    QObject *relatedObject() override;

public Q_SLOTS:
    void updated() override;

private:
    QBoxPlotLegendMarker *q_ptr;
    QBoxPlotSeries *m_series;

    Q_DECLARE_PUBLIC(QBoxPlotLegendMarker)
};

QT_END_NAMESPACE

#endif // QBOXPLOTLEGENDMARKER_P_H
