#include "xychartitem_p.h"
#include "qxyseries.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QPainter>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

XYChartItem::XYChartItem(QXYSeries* series, QGraphicsItem *parent):ChartItem(parent),
m_minX(0),
m_maxX(0),
m_minY(0),
m_maxY(0),
m_series(series)
{
    QObject::connect(series,SIGNAL(pointReplaced(int)),this,SLOT(handlePointReplaced(int)));
    QObject::connect(series,SIGNAL(pointAdded(int)),this,SLOT(handlePointAdded(int)));
    QObject::connect(series,SIGNAL(pointRemoved(int)),this,SLOT(handlePointRemoved(int)));

}

QPointF XYChartItem::calculateGeometryPoint(const QPointF& point) const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = (point.x() - m_minX)* deltaX;
    qreal y = (point.y() - m_minY)*-deltaY + m_size.height();
    return QPointF(x,y);
}


QPointF XYChartItem::calculateGeometryPoint(int index) const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = (m_series->x(index) - m_minX)* deltaX;
    qreal y = (m_series->y(index) - m_minY)*-deltaY + m_size.height();
    return QPointF(x,y);
}

QVector<QPointF> XYChartItem::calculateGeometryPoints() const
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

void XYChartItem::updatePoints(QVector<QPointF>& points)
{
    if(m_animator){
       m_animator->applyLayout(this,points);
    }
       else  setGeometry(points);

}

void XYChartItem::updatePoint(QVector<QPointF>& points)
{
    setGeometry(points);
}

void XYChartItem::setGeometry(QVector<QPointF>& points)
{
    m_points = points;
}

//handlers

void XYChartItem::handlePointAdded(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);

    QPointF point = calculateGeometryPoint(index);
    QVector<QPointF> points = m_points;
    points.insert(index,point);
    updatePoints(points);
    update();
}
void XYChartItem::handlePointRemoved(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);
    QPointF point = calculateGeometryPoint(index);
    QVector<QPointF> points = m_points;
    points.remove(index);
    updatePoints(points);
    update();
}

void XYChartItem::handlePointReplaced(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);
    QPointF point = calculateGeometryPoint(index);
    QVector<QPointF> points = m_points;
    points.replace(index,point);
    updatePoint(points);
    update();
}

void XYChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_minX=minX;
    m_maxX=maxX;
    m_minY=minY;
    m_maxY=maxY;

    if(isEmpty()) return;
    QVector<QPointF> points = calculateGeometryPoints();
    updatePoints(points);
    update();
}

void XYChartItem::handleGeometryChanged(const QRectF& rect)
{
	Q_ASSERT(rect.isValid());
	m_size=rect.size();
	m_clipRect=rect.translated(-rect.topLeft());
	setPos(rect.topLeft());

    if(isEmpty()) return;
	QVector<QPointF> points = calculateGeometryPoints();
	updatePoints(points);
	update();
}


bool XYChartItem::isEmpty()
{
   return !m_clipRect.isValid() ||  m_maxX - m_minX == 0 || m_maxY - m_minY ==0 ;
}

#include "moc_xychartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
