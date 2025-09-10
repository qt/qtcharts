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

#ifndef QCHARTVIEW_P_H
#define QCHARTVIEW_P_H

#include <QtCharts/QChartView>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QChart;
class ChartPresenter;
class QChartView;

class Q_CHARTS_EXPORT QChartViewPrivate
{
public:
    explicit QChartViewPrivate(QChartView *q, QChart *chart = 0);
    ~QChartViewPrivate();
    void setChart(QChart *chart);
    void resize();

protected:
    QChartView *q_ptr;

public:
    QGraphicsScene *m_scene;
    QChart *m_chart;
    QPoint m_rubberBandOrigin;
#ifndef QT_NO_RUBBERBAND
    QRubberBand *m_rubberBand;
#endif
    QChartView::RubberBands m_rubberBandFlags;
};

QT_END_NAMESPACE
#endif
