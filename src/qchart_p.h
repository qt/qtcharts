#ifndef QCHART_P_H
#define QCHART_P_H

#include "private/qgraphicswidget_p.h"
#include "qchartaxis.h"
#include "qlegend.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "chartbackground_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class QChartPrivate
{
public:
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

    Q_DECLARE_PUBLIC(QChart);
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif
