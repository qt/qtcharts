#include "splinepresenter_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplinePresenter::SplinePresenter(QSplineSeries* series, QGraphicsObject *parent) :
    LineChartItem(0, series, parent)//,m_boundingRect()
{
//    if (parent)
//        m_boundingRect = parent->boundingRect();
//    else
//        m_boundingRect = QRectF(10,50, 250, 250);
}

//void SplinePresenter::handleGeometryChanged(const QRectF&)
//{
//    update();
//}

//void SplinePresenter::handleDomainChanged(const Domain& domain)
//{
//    //
//}

QPointF SplinePresenter::calculateGeometryControlPoint(int index) const
{
    QSplineSeries* splineSeries = qobject_cast<QSplineSeries*>(m_series);
    const qreal deltaX = m_size.width()/m_domain.spanX();
    const qreal deltaY = m_size.height()/m_domain.spanY();
    qreal x = (splineSeries->controlPoint(index).x() - m_domain.m_minX)* deltaX;
    qreal y = (splineSeries->controlPoint(index).y() - m_domain.m_minY)*-deltaY + m_size.height();
    return QPointF(x,y);
}

void SplinePresenter::applyGeometry(QVector<QPointF>& points)
{
   if(points.size()==0) return;

//   QList<QGraphicsItem*> items = m_items.childItems();

   QPainterPath splinePath;
   const QPointF& point = points.at(0);
   splinePath.moveTo(point);
//   QGraphicsItem* item = items.at(0);
//   item->setPos(point.x()-1,point.y()-1);
//   if(!m_clipRect.contains(point)) item->setVisible(false);

   QSplineSeries* splineSeries = qobject_cast<QSplineSeries*>(m_series);
   for (int i = 0; i < splineSeries->count() - 1; i++)
       {
       const QPointF& point = points.at(i + 1);
//           painter->setPen(Qt::red);
//           splinePath.cubicTo(qobject_cast<QSplineSeries*>(m_series)->controlPoint(2 * i), qobject_cast<QSplineSeries*>(m_series)->controlPoint(2 * i + 1), QPointF(m_series->x(i + 1), m_series->y(i + 1)));
       splinePath.cubicTo(calculateGeometryControlPoint(2 * i), calculateGeometryControlPoint(2 * i + 1), point);
//           painter->drawEllipse(m_series->at(i), 4, 4);

//           painter->setPen(Qt::blue);
//           painter->drawLine(m_series->at(i), m_series->controlPoint(2 * i));
//           painter->drawLine(m_series->at(i + 1), m_series->controlPoint(2 * i + 1));
//           painter->drawEllipse(m_series->controlPoint(2 * i), 4, 4);
//           painter->drawEllipse(m_series->controlPoint(2 * i + 1), 4, 4);
       }

//   for(int i=1 ; i< points.size();i++) {
//       QGraphicsItem* item = items.at(i);
//       const QPointF& point = points.at(i);
//       item->setPos(point.x()-1,point.y()-1);
//       if(!m_clipRect.contains(point)) item->setVisible(false);
//       path.lineTo(point);
//   }

   prepareGeometryChange();
   m_path = splinePath;
   m_rect = splinePath.boundingRect();
}

//void SplinePresenter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(widget);
//    Q_UNUSED(option);
//    painter->save();

//    painter->setPen(Qt::SolidLine);

//    QPainterPath splinePath;
//    splinePath.moveTo(m_series->at(0));
//    for (int i = 0; i < m_series->count() - 1; i++)
//    {
//        painter->setPen(Qt::red);
//        splinePath.cubicTo(m_series->controlPoint(2 * i), m_series->controlPoint(2 * i + 1), m_series->at(i + 1));
//        painter->drawEllipse(m_series->at(i), 4, 4);

//        painter->setPen(Qt::blue);
//        painter->drawLine(m_series->at(i), m_series->controlPoint(2 * i));
//        painter->drawLine(m_series->at(i + 1), m_series->controlPoint(2 * i + 1));
//        painter->drawEllipse(m_series->controlPoint(2 * i), 4, 4);
//        painter->drawEllipse(m_series->controlPoint(2 * i + 1), 4, 4);
//    }
//    painter->setPen(Qt::red);
//    painter->drawPath(splinePath);
//    painter->restore();
//}

#include "moc_splinepresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
