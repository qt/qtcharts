#include "xylinechartitem_p.h"
#include "qxychartseries.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XYLineChartItem::XYLineChartItem(ChartPresenter* presenter, QXYChartSeries* series,QGraphicsItem *parent):ChartItem(parent),
m_presenter(presenter),
m_series(series),
m_dirtyData(false),
m_dirtyGeometry(false),
m_dirtyDomain(false)
{
}

QRectF XYLineChartItem::boundingRect() const
{
	return m_rect;
}

QPainterPath XYLineChartItem::shape() const
{
    return m_path;
}


void XYLineChartItem::addPoints(const QVector<QPointF>& points)
{
    m_data = points;
    for(int i=0; i<m_data.size();i++){
    const QPointF& point =m_data[i];
    QGraphicsRectItem* item = new QGraphicsRectItem(0,0,3,3,this);
    item->setPos(point.x()-1,point.y()-1);
    m_points << item;
    }
}

void XYLineChartItem::addPoint(const QPointF& point)
{
	m_data << point;
	QGraphicsRectItem* item = new QGraphicsRectItem(0,0,3,3,this);
	item->setPos(point.x()-1,point.y()-1);
	m_points << item;
}

void XYLineChartItem::removePoint(const QPointF& point)
{
    Q_ASSERT(m_data.count() == m_points.count());
    int index = m_data.lastIndexOf(point,0);
    m_data.remove(index);
    delete(m_points.takeAt(index));
}

void XYLineChartItem::setPoint(const QPointF& oldPoint,const QPointF& newPoint)
{
    Q_ASSERT(m_data.count() == m_points.count());
    int index = m_data.lastIndexOf(oldPoint,0);

    if(index > -1){
    m_data.replace(index,newPoint);
    QGraphicsItem* item = m_points.at(index);
    item->setPos(newPoint.x()-1,newPoint.y()-1);
    }
}

void XYLineChartItem::setPoint(int index,const QPointF& point)
{
    Q_ASSERT(m_data.count() == m_points.count());
    Q_ASSERT(index>=0);

    m_data.replace(index,point);
    QGraphicsItem* item = m_points.at(index);
    item->setPos(point.x()-1,point.y()-1);
}

void XYLineChartItem::clear()
{
	 qDeleteAll(m_points);
	 m_points.clear();
	 m_hash.clear();
	 m_path = QPainterPath();
	 m_rect = QRect();
	 m_data.clear();
}

void XYLineChartItem::clearView()
{
     qDeleteAll(m_points);
     m_points.clear();
     m_path = QPainterPath();
     m_rect = QRect();
     m_data.clear();
}

void XYLineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setPen(m_pen);
	painter->drawPath(m_path);
}

void XYLineChartItem::calculatePoint(QPointF& point, int index, const QXYChartSeries* series,const QSizeF& size, const Domain& domain) const
{
    const qreal deltaX = size.width()/domain.spanX();
    const qreal deltaY = size.height()/domain.spanY();
    qreal x = (series->x(index) - domain.m_minX)* deltaX;
    qreal y = (series->y(index) - domain.m_minY)*-deltaY + size.height();
    point.setX(x);
    point.setY(y);
}


void XYLineChartItem::calculatePoints(QVector<QPointF>& points, QHash<int,int>& hash,const QXYChartSeries* series,const QSizeF& size, const Domain& domain) const
{
    const qreal deltaX = size.width()/domain.spanX();
    const qreal deltaY = size.height()/domain.spanY();

    for (int i = 0; i < series->count(); ++i) {
      qreal x = (series->x(i) - domain.m_minX)* deltaX;
      if(x<0 || x > size.width()) continue;
      qreal y = (series->y(i) - domain.m_minY)*-deltaY + size.height();
      if(y<0 || y > size.height()) continue;
      hash[i] = points.size();
      points << QPointF(x,y);
    }
}

void XYLineChartItem::updateDomain()
{
    clear();
	calculatePoints(m_data,m_hash,m_series,m_size, m_domain);
	addPoints(m_data);
}

void XYLineChartItem::updateData()
{
    //for now the same
    updateDomain();
}

void XYLineChartItem::updateGeometry()
{

   if(m_data.size()==0) return;

   prepareGeometryChange();
   QPainterPath path;
   const QPointF& point = m_data.at(0);
   path.moveTo(point);

   foreach( const QPointF& point , m_data) {
       path.lineTo(point);
   }

   m_path = path;
   m_rect = path.boundingRect();
}

void XYLineChartItem::setPen(const QPen& pen)
{
    m_pen = pen;
}

//handlers

void XYLineChartItem::handleModelChanged(int index)
{
    Q_ASSERT(index<m_series->count());
    if(m_hash.contains(index)){
        int i = m_hash.value(index);
        QPointF point;
        calculatePoint(point,index,m_series,m_size,m_domain);
        setPoint(i,point);
    }
    update();
}

void XYLineChartItem::handleDomainChanged(const Domain& domain)
{
    m_domain = domain;
    updateDomain();
    update();
}

void XYLineChartItem::handleGeometryChanged(const QRectF& rect)
{
    Q_ASSERT(rect.isValid());

    m_size=rect.size();
    updateDomain();
    updateGeometry();
    setPos(rect.topLeft());
    update();
}


#include "moc_xylinechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
