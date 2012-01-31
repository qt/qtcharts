#include "xylinechartitem_p.h"
#include "axisitem_p.h"
#include "qxychartseries.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XYLineChartItem::XYLineChartItem(QXYChartSeries* series,QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_series(series),
    m_pathItem(new QGraphicsPathItem(this))
{
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);
}

void XYLineChartItem::setPos(const QPointF & pos)
{
    QGraphicsItem::setPos(pos);
}

void XYLineChartItem::resize(const QSize &size)
{
    m_rect = QRect(0, 0, size.width(), size.height());
    prepareGeometryChange();
    updateGeometry();
}

void XYLineChartItem::setTheme(ChartTheme *theme)
{
    if (theme) {
        m_theme = theme->themeForSeries();
        prepareGeometryChange();
        updateGeometry();
    }
}

void XYLineChartItem::setPlotDomain(const PlotDomain& data)
{
    m_plotDomain=data;
    prepareGeometryChange();
    updateGeometry();

}

QRectF XYLineChartItem::boundingRect() const
{
	return m_rect;
}
/*
QPainterPath XYLineChartItem::shape() const
{
    return m_pathItem->shape();
}
*/
void XYLineChartItem::updateGeometry()
{
   if (!m_rect.isValid()) return;

   const qreal deltaX = m_rect.width()/m_plotDomain.spanX();
   const qreal deltaY = m_rect.height()/m_plotDomain.spanY();

   QPainterPath path;

   for (int j = 0; j < m_series->count(); ++j) {
       qreal dx = m_series->x(j) - m_plotDomain.m_minX;
       qreal dy = m_series->y(j) - m_plotDomain.m_minY;
       qreal x = (dx * deltaX) + m_rect.left();
       qreal y = - (dy * deltaY) + m_rect.bottom();
       if(j==0) path.moveTo(x,y);
       else path.lineTo(x,y);
   }

   m_pathItem->setPath(path);
   m_pathItem->setPen(m_theme.linePen);
   m_pathItem->setBrush(Qt::NoBrush);
}


QTCOMMERCIALCHART_END_NAMESPACE
