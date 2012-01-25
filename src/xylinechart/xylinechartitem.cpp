#include "xylinechartitem_p.h"
#include "axisitem_p.h"
#include "qxychartseries.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XYLineChartItem::XYLineChartItem(QXYChartSeries* series,QGraphicsItem *parent):ChartItem(parent),
m_series(series),
m_dirty(false)
{

}

void XYLineChartItem::setSize(const QSize& size)
{
    m_rect=QRect(0,0,size.width(),size.height());
    m_dirty=true;
}

void XYLineChartItem::setPlotDomain(const PlotDomain& data)
{
    m_plotDomain=data;
    m_dirty=true;
}

QRectF XYLineChartItem::boundingRect() const
{
	return m_polyline.boundingRect();
}

void XYLineChartItem::updateGeometry()
{
   if (!m_rect.isValid()) return;

   const qreal deltaX = (m_rect.width()-1)/m_plotDomain.spanX();
   const qreal deltaY = (m_rect.height()-1)/m_plotDomain.spanY();

   m_polyline.clear();
   m_polyline.resize(m_series->count());

   for (int j = 0; j < m_series->count(); ++j) {
       qreal dx = m_series->x(j) - m_plotDomain.m_minX;
       qreal dy = m_series->y(j) - m_plotDomain.m_minY;
       qreal x = (dx * deltaX) + m_rect.left();
       qreal y = - (dy * deltaY) + m_rect.bottom();
       m_polyline[j] = QPointF(x, y);
   }

}


void XYLineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    //TODO: remove it
    if (m_dirty) {
        updateGeometry();
        m_dirty=false;
    }
    painter->setClipRect(m_rect.adjusted(+1, +1, -1, -1));
    painter->setPen(m_series->color());
    painter->drawPolyline(m_polyline);
}

QTCOMMERCIALCHART_END_NAMESPACE
