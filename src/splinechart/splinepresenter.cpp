#include "splinepresenter_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplinePresenter::SplinePresenter(QSplineSeries* series, QGraphicsObject *parent) :
    LineChartItem(series, parent)//,m_boundingRect()
{
    //
}



QPointF SplinePresenter::calculateGeometryControlPoint(int index) const
{
    QSplineSeries* splineSeries = qobject_cast<QSplineSeries*>(m_series);
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = (splineSeries->controlPoint(index).x() - m_minX)* deltaX;
    qreal y = (splineSeries->controlPoint(index).y() - m_minY)*-deltaY + m_size.height();
    return QPointF(x,y);
}

void SplinePresenter::applyGeometry(QVector<QPointF>& points)
{
    if(points.size()==0) return;

    QPainterPath splinePath;
    const QPointF& point = points.at(0);
    splinePath.moveTo(point);

//    QSplineSeries* splineSeries = qobject_cast<QSplineSeries*>(m_series);
    for (int i = 0; i < points.size() - 1; i++)
    {
        const QPointF& point = points.at(i + 1);
        splinePath.cubicTo(calculateGeometryControlPoint(2 * i), calculateGeometryControlPoint(2 * i + 1), point);
    }



    prepareGeometryChange();
    m_path = splinePath;
    m_rect = splinePath.boundingRect();
}

void SplinePresenter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->save();
    painter->setPen(m_pen);
    painter->setClipRect(m_clipRect);
    painter->drawPath(m_path);

    QSplineSeries* splineSeries = qobject_cast<QSplineSeries*>(m_series);
    for (int i = 0; i < m_points.size() - 1; i++)
    {
        painter->setPen(Qt::red);
        painter->drawEllipse(m_points[i], 2, 2);

        painter->setPen(Qt::blue);
        //        painter->drawLine(m_series->at(i), m_series->controlPoint(2 * i));
        //        painter->drawLine(m_series->at(i + 1), m_series->controlPoint(2 * i + 1));
        //        painter->drawEllipse(calculateGeometryControlPoint(2 * i), 4, 4);
        //        painter->drawEllipse(calculateGeometryControlPoint(2 * i + 1), 4, 4);
    }
    if (m_points.count() > 0)
    {
        painter->setPen(Qt::red);
        painter->drawEllipse(m_points[m_points.count() - 1], 2, 2);
    }
    painter->restore();
}

#include "moc_splinepresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
