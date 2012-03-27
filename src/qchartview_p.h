//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QCHARTVIEW_P_H
#define QCHARTVIEW_P_H

#include "qchartview.h"

class QGraphicsScene;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

struct QChartViewPrivate {

    QChartViewPrivate();
    ~QChartViewPrivate();

    QGraphicsScene *m_scene;
    QChart *m_chart;
    ChartPresenter *m_presenter;
    QPoint m_rubberBandOrigin;
    QRubberBand *m_rubberBand;
    QChartView::RubberBands m_rubberBandFlags;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif
