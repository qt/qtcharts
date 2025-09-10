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

#ifndef QXYLEGENDMARKER_P_H
#define QXYLEGENDMARKER_P_H

#include <QtCharts/QChartGlobal>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <QtCharts/QXYSeries>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QXYLegendMarker;

class Q_CHARTS_EXPORT QXYLegendMarkerPrivate : public QLegendMarkerPrivate
{
    Q_OBJECT
public:
    explicit QXYLegendMarkerPrivate(QXYLegendMarker *q, QXYSeries *series, QLegend *legend);
    virtual ~QXYLegendMarkerPrivate();

    QAbstractSeries* series() override;
    QObject* relatedObject() override;

public Q_SLOTS:
    void updated() override;

private:
    QXYLegendMarker *q_ptr;
    QXYSeries *m_series;

    Q_DECLARE_PUBLIC(QXYLegendMarker)
};

QT_END_NAMESPACE

#endif // QXYLEGENDMARKER_P_H
