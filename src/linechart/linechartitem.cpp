#include "linechartitem_p.h"
#include "qlineseries.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

LineChartItem::LineChartItem(QLineSeries* series,QGraphicsItem *parent):XYChartItem(series,parent),
m_series(series),
m_pointsVisible(false)
{
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(series,SIGNAL(updated()),this,SLOT(handleUpdated()));
    QObject::connect(this,SIGNAL(clicked(const QPointF&)),series,SIGNAL(clicked(const QPointF&)));
    handleUpdated();
}

QRectF LineChartItem::boundingRect() const
{
	return m_rect;
}

QPainterPath LineChartItem::shape() const
{
    return m_path;
}

void LineChartItem::setGeometry(QVector<QPointF>& points)
{
    if(points.size()==0) return;

    QList<QGraphicsItem*> items = m_items.childItems();

    QPainterPath linePath(points.at(0));

    for(int i=1; i< points.size();i++) {
        linePath.lineTo(points.at(i));
    }

    prepareGeometryChange();
    m_path = linePath;
    m_rect = linePath.boundingRect();

    XYChartItem::setGeometry(points);
}

void LineChartItem::handleUpdated()
{
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2*m_pointPen.width());
    update();
}

//painter

void LineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->save();
    painter->setPen(m_linePen);
    painter->setClipRect(clipRect());
    painter->drawPath(m_path);
    if(m_pointsVisible){
    	painter->setPen(m_pointPen);
    	painter->drawPoints(points());
    }
    painter->restore();
}

void LineChartItem::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
    emit clicked(calculateDomainPoint(event->pos()));
}

#include "moc_linechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
