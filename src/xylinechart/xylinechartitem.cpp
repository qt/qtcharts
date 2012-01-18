#include "xylinechartitem_p.h"
#include "axis_p.h"
#include "xygrid_p.h"
#include "qxychartseries.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

QCHART_BEGIN_NAMESPACE

XYLineChartItem::XYLineChartItem(QXYChartSeries* series,QGraphicsItem *parent):QGraphicsItem(parent),
m_series(series),
m_dirtyGeometry(true)
{

}

void XYLineChartItem::setChartSize(const QRectF& rect)
{
	m_rect = rect;
	m_dirtyGeometry = true;
}

void XYLineChartItem::setXYPlotData(const XYPlotData& data){
    m_xyPlotData=data;
    m_dirtyGeometry = true;
}

QRectF XYLineChartItem::boundingRect() const
{
	return m_polyline.boundingRect();
}


void XYLineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    if(m_dirtyGeometry) {

        m_dirtyGeometry=false;

        if (!m_rect.isValid())
        return;

        painter->setClipRect(m_rect.adjusted(+1, +1, -1, -1));

        const qreal deltaX = (m_rect.width()-1)/m_xyPlotData.spanX();
        const qreal deltaY = (m_rect.height()-1)/m_xyPlotData.spanY();

        m_polyline.clear();
        m_polyline.resize(m_series->count());

        for (int j = 0; j < m_series->count(); ++j) {
            qreal dx = m_series->x(j) - m_xyPlotData.m_minX;
            qreal dy = m_series->y(j) - m_xyPlotData.m_minY;
            qreal x = (dx * deltaX) + m_rect.left();
            qreal y = - (dy * deltaY) + m_rect.bottom();
            m_polyline[j] = QPointF(x, y);
        }
        painter->setPen(m_series->color());
        painter->drawPolyline(m_polyline);
    }

    painter->setClipRect(m_rect.adjusted(+1, +1, -1, -1));
    painter->setPen(m_series->color());
    painter->drawPolyline(m_polyline);

}

QCHART_END_NAMESPACE
