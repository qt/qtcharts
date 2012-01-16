#include "xygrid_p.h"
#include "xylinechart_p.h"
#include <QPainter>

QCHART_BEGIN_NAMESPACE

XYGrid::XYGrid(const XYLineChart* const chart, QGraphicsItem* parent):QGraphicsItem(parent),
m_chart(chart)
{
}

XYGrid::~XYGrid()
{
    // TODO Auto-generated destructor stub
}

void XYGrid::setSize(const QSizeF& size) {
	m_rect.setSize(size.toSize());
}


QRectF XYGrid::boundingRect() const
{
	return m_rect;
}

void XYGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	if (!m_rect.isValid())
		return;

		const XYPlotData& plotData = m_chart->xyPlotData();

		const qreal deltaX = (m_rect.width() -1) / plotData.ticksX();
		const qreal deltaY = (m_rect.height() - 1) / plotData.ticksY();

		for (int i = 0; i <= plotData.ticksX(); ++i) {

			int x = i * deltaX + m_rect.left();
			qreal label = plotData.m_minX + (i * plotData.spanX()
					/ plotData.ticksX());
			painter->drawLine(x, m_rect.top()+1, x, m_rect.bottom());
			//painter->drawLine(x, m_rect.bottom(), x, m_rect.bottom() + 5);

			painter->drawText(x - 50, m_rect.bottom() + 5, 100, 20,
					Qt::AlignHCenter | Qt::AlignTop,
					QString::number(label));
		}

		for (int j = 0; j <= plotData.ticksY(); ++j) {

			int y = j * -deltaY + m_rect.bottom();
			qreal label = plotData.m_minY + (j * plotData.spanY()
					/ plotData.ticksY());

			painter->drawLine(m_rect.left(), y, m_rect.right()-1, y);
			//painter->drawLine(m_rect.left() - 5, y, m_rect.left(), y);
			//TODO : margin = 50 ;
			painter->drawText(m_rect.left() - 50, y - 10, 50 - 5, 20,
					Qt::AlignRight | Qt::AlignVCenter,
					QString::number(label));
		}

		//painter->drawRect(m_rect.adjusted(0, 0, -1, -1));
}

QCHART_END_NAMESPACE
