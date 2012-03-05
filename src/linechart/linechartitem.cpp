#include "linechartitem_p.h"
#include "qlineseries.h"
#include "chartpresenter_p.h"
#include <QPainter>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

LineChartItem::LineChartItem(QLineSeries* series,QGraphicsItem *parent):ChartItem(parent),
m_minX(0),
m_maxX(0),
m_minY(0),
m_maxY(0),
m_series(series),
m_items(this)
{
	//m_items.setZValue(ChartPresenter::LineChartZValue);
    setZValue(ChartPresenter::LineChartZValue);

    QObject::connect(series,SIGNAL(pointReplaced(int)),this,SLOT(handlePointReplaced(int)));
    QObject::connect(series,SIGNAL(pointAdded(int)),this,SLOT(handlePointAdded(int)));
    QObject::connect(series,SIGNAL(pointRemoved(int)),this,SLOT(handlePointRemoved(int)));
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

void LineChartItem::clearPoints(int count)
{
    QList<QGraphicsItem *> items = m_items.childItems();

    for (int i = 0; i < count; ++i) {
        delete(items.takeLast());
    }
}

QPointF LineChartItem::calculateGeometryPoint(int index) const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = (m_series->x(index) - m_minX)* deltaX;
    qreal y = (m_series->y(index) - m_minY)*-deltaY + m_size.height();
    return QPointF(x,y);
}

QVector<QPointF> LineChartItem::calculateGeometryPoints() const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);

    QVector<QPointF> points;
    points.reserve(m_series->count());
    for (int i = 0; i < m_series->count(); ++i) {
      qreal x = (m_series->x(i) - m_minX)* deltaX;
      qreal y = (m_series->y(i) - m_minY)*-deltaY + m_size.height();
      points << QPointF(x,y);
    }
    return points;
}

void LineChartItem::updateAllPoints()
{
    QVector<QPointF> points = calculateGeometryPoints();

    int diff = m_points.size() - points.size();

    if(diff>0) {
        clearPoints(diff);
    }
    else if(diff<0) {
        createPoints(-diff);
    }

	setGeometry(points);
}

void LineChartItem::updatePoints(QVector<QPointF>& points)
{
    int diff = m_points.size() - points.size();

     if(diff>0) {
         clearPoints(diff);
     }
     else if(diff<0) {
         createPoints(-diff);
     }

     setGeometry(points);
}

void LineChartItem::updatePoint(int index,QPointF& newPoint)
{
	m_points.replace(index,newPoint);
	setGeometry(m_points);
}

void LineChartItem::setGeometry(QVector<QPointF>& points)
{
   if(points.size()==0) return;

   QList<QGraphicsItem*> items = m_items.childItems();

   QPainterPath path;
   const QPointF& point = points.at(0);
   path.moveTo(point);
   QGraphicsItem* item = items.at(0);
   item->setPos(point.x()-1,point.y()-1);
   if(!m_clipRect.contains(point)) {
	   item->setVisible(false);
   }else{
	   item->setVisible(true);
   }

   for(int i=1 ; i< points.size();i++) {
       QGraphicsItem* item = items.at(i);
       const QPointF& point = points.at(i);
       item->setPos(point.x()-1,point.y()-1);
       if(!m_clipRect.contains(point)) {
    	   item->setVisible(false);
       }else{
    	   item->setVisible(true);
       }
       path.lineTo(point);
   }

   prepareGeometryChange();
   m_path = path;
   m_rect = path.boundingRect();
   m_points = points;
}

void LineChartItem::setPen(const QPen& pen)
{
    m_pen = pen;
}

//handlers

void LineChartItem::handlePointAdded(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);

    QPointF point = calculateGeometryPoint(index);
    createPoints(1);
    QVector<QPointF> points = m_points;
    points.insert(index,point);

    updatePoints(points);
    update();
}
void LineChartItem::handlePointRemoved(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);

    QPointF point = calculateGeometryPoint(index);
    clearPoints(1);
    QVector<QPointF> points = m_points;
    points.remove(index);
    updatePoints(points);
    update();
}

void LineChartItem::handlePointReplaced(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);
    QPointF point = calculateGeometryPoint(index);
    updatePoint(index,point);
    update();
}

void LineChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_minX=minX;
    m_maxX=maxX;
    m_minY=minY;
    m_maxY=maxY;

    if(isEmpty()) return;
    updateAllPoints();
    update();
}

void LineChartItem::handleGeometryChanged(const QRectF& rect)
{
	Q_ASSERT(rect.isValid());
	m_size=rect.size();
	m_clipRect=rect.translated(-rect.topLeft());
	setPos(rect.topLeft());

	if(isEmpty()) return;
	updateAllPoints();
	update();
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
    painter->setClipRect(m_clipRect);
    painter->drawPath(m_path);
    painter->restore();
}

bool LineChartItem::isEmpty()
{
   return !m_clipRect.isValid() ||  m_maxX - m_minX == 0 || m_maxY - m_minY ==0 ;
}

#include "moc_linechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
