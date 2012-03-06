#include "linechartitem_p.h"
#include "qlineseries.h"
#include "chartpresenter_p.h"
#include <QPainter>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

LineChartItem::LineChartItem(QLineSeries* series,QGraphicsItem *parent):XYChartItem(series,parent),
m_series(series),
m_items(this)
{
	//m_items.setZValue(ChartPresenter::LineChartZValue);
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(series,SIGNAL(updated()),this,SLOT(handleUpdated()));

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

void LineChartItem::createPoints(int count)
{
    for (int i = 0; i < count; ++i) {
        QGraphicsRectItem* item = new QGraphicsRectItem(0,0,3,3);
        m_items.addToGroup(item);
    }
}

void LineChartItem::deletePoints(int count)
{
    QList<QGraphicsItem *> items = m_items.childItems();

    for (int i = 0; i < count; ++i) {
        delete(items.takeLast());
    }
}

void LineChartItem::setGeometry(QVector<QPointF>& points)
{
    if(points.size()==0) return;

    int diff =  XYChartItem::points().size() - points.size();

    if(diff>0) {
        deletePoints(diff);
    }
    else if(diff<0) {
        createPoints(-diff);
    }

    QList<QGraphicsItem*> items = m_items.childItems();

    QPainterPath path;
    const QPointF& point = points.at(0);
    path.moveTo(point);
    QGraphicsItem* item = items.at(0);
    item->setPos(point.x()-1,point.y()-1);
    if(!clipRect().contains(point)) {
        item->setVisible(false);
    }
    else {
        item->setVisible(true);
    }

    for(int i=1; i< points.size();i++) {
        QGraphicsItem* item = items.at(i);
        const QPointF& point = points.at(i);
        item->setPos(point.x()-1,point.y()-1);
        if(!clipRect().contains(point)) {
            item->setVisible(false);
        }
        else {
            item->setVisible(true);
        }
        path.lineTo(point);
    }

    prepareGeometryChange();
    m_path = path;
    m_rect = path.boundingRect();

    XYChartItem::setGeometry(points);
}

void LineChartItem::setPen(const QPen& pen)
{
    m_pen = pen;
}


void LineChartItem::handleUpdated()
{
    m_items.setVisible(m_series->pointsVisible());
    setPen(m_series->pen());
    update();
}

//painter

void LineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->save();
    painter->setPen(m_pen);
    painter->setClipRect(clipRect());
    painter->drawPath(m_path);
    painter->restore();
}

#include "moc_linechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
