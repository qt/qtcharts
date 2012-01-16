#include "xylinechart_p.h"
#include "axis_p.h"
#include "xygrid_p.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

QCHART_BEGIN_NAMESPACE

XYLineChart::XYLineChart(QGraphicsItem *parent):QChart(parent),
m_axisX(new Axis(this)),
m_axisY(new Axis(this)),
m_grid(new XYGrid(this,this)),
m_plotDataIndex(0)
{
	// set axis
	m_axisY->rotate(90);

	XYPlotData data;
	data.m_minX = 0.0;
	data.m_maxX = 100.0;
	data.m_minY = 0.0;
	data.m_maxY = 100.0;
	data.m_ticksX=4;
	data.m_ticksY=4;

	m_plotDataList.clear();
	m_plotDataList << data;

}

void XYLineChart::setSize(const QSizeF& size) {

	m_rect = QRect(QPoint(0,0),size.toSize());
	m_rect.adjust(margin(),margin(),-margin(),-margin());
	updateGeometry();
}

void XYLineChart::addXYSeries(const QXYSeries* series)
{
	m_series<<series;
}

QRectF XYLineChart::boundingRect() const
{
	return m_rect;
}

void XYLineChart::updateGeometry()
{
	//m_axisX->setPos(m_rect.bottomLeft());
	//m_axisX->setLength(m_rect.width());
	//m_axisY->setLength(m_rect.height());
	m_grid->setPos(m_rect.topLeft());
	m_grid->setSize(m_rect.size());
	update();
}

void XYLineChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	const XYPlotData& xyplotData = xyPlotData();

	if (!m_rect.isValid())
	return;

	painter->setClipRect(m_rect.adjusted(+1, +1, -1, -1));

	const qreal deltaX = (m_rect.width()-1)/xyplotData.spanX();
	const qreal deltaY = (m_rect.height()-1)/xyplotData.spanY();

	foreach (const QXYSeries* series, m_series) {

		QPolygonF polyline(series->count());

		for (int j = 0; j < series->count(); ++j) {
			qreal dx = series->x(j) - xyplotData.m_minX;
			qreal dy = series->y(j) - xyplotData.m_minY;
			qreal x = (dx * deltaX) + m_rect.left();
			qreal y = - (dy * deltaY) + m_rect.bottom();
			polyline[j] = QPointF(x, y);
		}
		painter->setPen(series->color());
		painter->drawPolyline(polyline);
	}
}
QCHART_END_NAMESPACE
