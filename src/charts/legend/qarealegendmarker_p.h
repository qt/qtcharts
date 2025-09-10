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

#ifndef QAREALEGENDMARKER_P_H
#define QAREALEGENDMARKER_P_H

#include <QtCharts/QChartGlobal>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <QtCharts/QAreaSeries>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QAreaLegendMarker;

class Q_CHARTS_EXPORT QAreaLegendMarkerPrivate : public QLegendMarkerPrivate
{
    Q_OBJECT
public:
    explicit QAreaLegendMarkerPrivate(QAreaLegendMarker *q, QAreaSeries *series, QLegend *legend);
    virtual ~QAreaLegendMarkerPrivate();

    QAreaSeries* series() override;
    QObject* relatedObject() override;

public Q_SLOTS:
    void updated() override;

private:
    QAreaLegendMarker *q_ptr;
    QAreaSeries *m_series;

    Q_DECLARE_PUBLIC(QAreaLegendMarker)
};

QT_END_NAMESPACE

#endif // QAREALEGENDMARKER_P_H
