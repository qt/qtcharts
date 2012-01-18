#include "qchart.h"
#include "qchartseries.h"
#include "xylinechartitem_p.h"
#include "xyplotdata_p.h"
#include "axis_p.h"
#include "xygrid_p.h"
#include <QDebug>

QCHART_BEGIN_NAMESPACE

QChart::QChart(QGraphicsItem* parent):QGraphicsItem(parent),
m_marginSize(0),
m_axisX(new Axis(this)),
m_axisY(new Axis(this)),
m_grid(new XYGrid(this)),
m_plotDataIndex(0)
{
  //  setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    // set axis
        m_axisY->rotate(90);


        //TODO hardcoded values , to removed soon
        XYPlotData* data = new XYPlotData();
        data->m_minX = 0.0;
        data->m_maxX = 100.0;
        data->m_minY = 0.0;
        data->m_maxY = 100.0;
        data->m_ticksX=4;
        data->m_ticksY=4;

        m_plotDataList.clear();
        m_plotDataList << data;

        m_grid->setZValue(10);
        m_grid->setXYPlotData(*m_plotDataList.at(0));
}

QChart::~QChart(){}

QRectF QChart::boundingRect() const
{
    return m_rect;
}

void QChart::addSeries(QChartSeries* series)
{
    m_series<<series;

    switch(series->type())
    {
    case QChartSeries::LINE:
        XYLineChartItem* item = new XYLineChartItem(reinterpret_cast<QXYChartSeries*>(series),this);
        item->setXYPlotData(*m_plotDataList.at(0));
        m_items<<item;
        break;
    }
}

void QChart::setSize(const QSizeF& size) {
    //TODO refactor to setGeometry
    m_rect = QRect(QPoint(0,0),size.toSize());
    m_rect.adjust(margin(),margin(),-margin(),-margin());
    m_grid->setPos(m_rect.topLeft());
    m_grid->setSize(m_rect.size());
    foreach(QGraphicsItem* item , m_items)
    reinterpret_cast<XYLineChartItem*>(item)->setChartSize(m_rect);
    update();

}

void QChart::setMargin(int margin)
{
    m_marginSize = margin;
}

QCHART_END_NAMESPACE
