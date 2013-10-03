/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QCHARTVIEW_P_H
#define QCHARTVIEW_P_H

#include "qchartview.h"

class QGraphicsScene;
class ChartPresenter;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QChartView;

class QChartViewPrivate
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

QTCOMMERCIALCHART_END_NAMESPACE
#endif
