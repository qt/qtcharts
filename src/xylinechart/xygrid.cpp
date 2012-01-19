#include "xygrid_p.h"
#include <QPainter>
#include <QDebug>

QCHART_BEGIN_NAMESPACE

XYGrid::XYGrid(QGraphicsItem* parent):QGraphicsItem(parent)
{
}

XYGrid::~XYGrid()
{
    // TODO Auto-generated destructor stub
}

void XYGrid::setSize(const QSizeF& size)
{
	m_rect.setSize(size.toSize());
}

void XYGrid::setXYPlotData(const XYPlotDomain& xyPlotData)
{
    m_xyPlotData = xyPlotData;
}

QRectF XYGrid::boundingRect() const
{
	return m_rect;
}

void XYGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{

    if (!m_rect.isValid())
    return;

    const qreal deltaX = (m_rect.width() -1) / m_xyPlotData.ticksX();
    const qreal deltaY = (m_rect.height() - 1) / m_xyPlotData.ticksY();

    for (int i = 0; i <= m_xyPlotData.ticksX(); ++i) {

        int x = i * deltaX + m_rect.left();
        qreal label = m_xyPlotData.m_minX + (i * m_xyPlotData.spanX()
            / m_xyPlotData.ticksX());
        painter->drawLine(x, m_rect.top()+1, x, m_rect.bottom());
        //painter->drawLine(x, m_rect.bottom(), x, m_rect.bottom() + 5);

        painter->drawText(x - 50, m_rect.bottom() + 5, 100, 20,
            Qt::AlignHCenter | Qt::AlignTop,
            QString::number(label));
    }

    for (int j = 0; j <= m_xyPlotData.ticksY(); ++j) {

        int y = j * -deltaY + m_rect.bottom();
        qreal label = m_xyPlotData.m_minY + (j * m_xyPlotData.spanY()
            / m_xyPlotData.ticksY());

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
