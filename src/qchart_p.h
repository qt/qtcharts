//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QCHART_P_H
#define QCHART_P_H

#include "qchartaxis.h"
#include "qlegend.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "chartbackground_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

struct QChartPrivate
{
    QChartPrivate(QChart *parent);
    ~QChartPrivate();

    void createChartBackgroundItem();
    void createChartTitleItem();
    void updateLayout();
    void updateLegendLayout();

    QChart *q_ptr;
    ChartBackground* m_backgroundItem;
    QGraphicsSimpleTextItem* m_titleItem;
    QRectF m_rect;
    QLegend* m_legend;
    ChartDataSet *m_dataset;
    ChartPresenter *m_presenter;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif
