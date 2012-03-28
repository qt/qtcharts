#include "xychartitem_p.h"
#include "qxyseries.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

XYChartItem::XYChartItem(QXYSeries *series, ChartPresenter *presenter):ChartItem(presenter),
    m_minX(0),
    m_maxX(0),
    m_minY(0),
    m_maxY(0),
    m_series(series)
{
    connect(series,SIGNAL(pointReplaced(int)),this,SLOT(handlePointReplaced(int)));
    connect(series,SIGNAL(pointAdded(int)),this,SLOT(handlePointAdded(int)));
    connect(series,SIGNAL(pointRemoved(int)),this,SLOT(handlePointRemoved(int)));
    connect(this,SIGNAL(clicked(const QPointF&)),series,SIGNAL(clicked(const QPointF&)));
}

QPointF XYChartItem::calculateGeometryPoint(const QPointF &point) const
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

QPointF XYChartItem::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = point.x()/deltaX +m_minX;
    qreal y = (point.y()-m_size.height())/(-deltaY)+ m_minY;
    return QPointF(x,y);
}

void XYChartItem::updateLayout(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints,int index)
{
    if (animator()) {
        animator()->updateLayout(this,oldPoints,newPoints,index);
    } else {
        setLayout(newPoints);
    }
}

void XYChartItem::setLayout(QVector<QPointF> &points)
{
    m_points = points;
    update();
}

//handlers

void XYChartItem::handlePointAdded(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);
    QPointF point = calculateGeometryPoint(index);
    QVector<QPointF> points = m_points;
    points.insert(index,point);
    updateLayout(m_points,points,index);
    update();
}
void XYChartItem::handlePointRemoved(int index)
{
    Q_ASSERT(index<m_series->count() + 1);
    Q_ASSERT(index>=0);
    QVector<QPointF> points = m_points;
    points.remove(index);
    updateLayout(m_points,points,index);
    update();
}

void XYChartItem::handlePointReplaced(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);
    QPointF point = calculateGeometryPoint(index);
    QVector<QPointF> points = m_points;
    points.replace(index,point);
    updateLayout(m_points,points,index);
    update();
}

void XYChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_minX=minX;
    m_maxX=maxX;
    m_minY=minY;
    m_maxY=maxY;

    if (isEmpty()) return;
    QVector<QPointF> points = calculateGeometryPoints();
    updateLayout(m_points,points);
    update();
}

void XYChartItem::handleGeometryChanged(const QRectF &rect)
{
	Q_ASSERT(rect.isValid());
	m_size=rect.size();
	m_clipRect=rect.translated(-rect.topLeft());
	setPos(rect.topLeft());

    if (isEmpty()) return;
	QVector<QPointF> points = calculateGeometryPoints();
	updateLayout(m_points,points);
	update();
}


bool XYChartItem::isEmpty()
{
   return !m_clipRect.isValid() || qFuzzyIsNull(m_maxX - m_minX) || qFuzzyIsNull(m_maxY - m_minY);
}

void XYChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(calculateDomainPoint(event->pos()));
}

#include "moc_xychartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
