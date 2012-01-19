#include "xylinechartitem_p.h"
#include "axis_p.h"
#include "xygrid_p.h"
#include "qxychartseries.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XYLineChartItem::XYLineChartItem(QXYChartSeries* series,QGraphicsItem *parent):QGraphicsItem(parent),
m_series(series)
{

}

void XYLineChartItem::updateXYPlotData(const XYPlotDomain& data)
{
    m_xyPlotData=data;

    if (!m_xyPlotData.m_viewportRect.isValid())
    return;

    const QRect& rect =  m_xyPlotData.m_viewportRect;

    const qreal deltaX = (rect.width()-1)/m_xyPlotData.spanX();
    const qreal deltaY = (rect.height()-1)/m_xyPlotData.spanY();

    m_polyline.clear();
    m_polyline.resize(m_series->count());

    for (int j = 0; j < m_series->count(); ++j) {
        qreal dx = m_series->x(j) - m_xyPlotData.m_minX;
        qreal dy = m_series->y(j) - m_xyPlotData.m_minY;
        qreal x = (dx * deltaX) + rect.left();
        qreal y = - (dy * deltaY) + rect.bottom();
        m_polyline[j] = QPointF(x, y);
    }

}

QRectF XYLineChartItem::boundingRect() const
{
	return m_polyline.boundingRect();
}


void XYLineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->setClipRect(m_xyPlotData.m_viewportRect.adjusted(+1, +1, -1, -1));
    painter->setPen(m_series->color());
    painter->drawPolyline(m_polyline);

}

QTCOMMERCIALCHART_END_NAMESPACE
