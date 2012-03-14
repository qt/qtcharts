#include "splinechartitem_p.h"
#include "chartpresenter_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplineChartItem::SplineChartItem(QSplineSeries* series, QGraphicsItem *parent) :
XYChartItem(series, parent),
m_series(series)
{
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(series,SIGNAL(updated()),this,SLOT(handleUpdated()));
    handleUpdated();
}

QRectF SplineChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath SplineChartItem::shape() const
{
    return m_path;
}

QPointF SplineChartItem::calculateGeometryControlPoint(int index) const
{
    return XYChartItem::calculateGeometryPoint(m_series->controlPoint(index));
}

void SplineChartItem::setLayout(QVector<QPointF>& points)
{

    if(points.size()==0)
    {
        XYChartItem::setLayout(points);
        return;
    }

    QPainterPath splinePath;
    const QPointF& point = points.at(0);
    splinePath.moveTo(point);

    for (int i = 0; i < points.size() - 1; i++)
    {
        const QPointF& point = points.at(i + 1);
        splinePath.cubicTo(calculateGeometryControlPoint(2 * i), calculateGeometryControlPoint(2 * i + 1), point);
    }

    prepareGeometryChange();
    m_path = splinePath;
    m_rect = splinePath.boundingRect();
    XYChartItem::setLayout(points);
}

//handlers

void SplineChartItem::handleUpdated()
{
    m_pen = m_series->pen();
    update();
}

//painter

void SplineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->save();
    painter->setClipRect(clipRect());
//    painter->setPen(m_pen);
    painter->setPen(m_series->pen());
    painter->drawPath(m_path);

//    const QVector<QPointF> points =  XYChartItem::points();

//    for (int i = 0; i < points.size() - 1; i++)
//    {
//        painter->setPen(Qt::red);
//        painter->drawEllipse(points[i], 2, 2);

//        painter->setPen(Qt::blue);
//        //        painter->drawLine(m_series->at(i), m_series->controlPoint(2 * i));
//        //        painter->drawLine(m_series->at(i + 1), m_series->controlPoint(2 * i + 1));
//        //        painter->drawEllipse(calculateGeometryControlPoint(2 * i), 4, 4);
//        //        painter->drawEllipse(calculateGeometryControlPoint(2 * i + 1), 4, 4);
//    }
//    if (points.count() > 0)
//    {
//        painter->setPen(Qt::red);
//        painter->drawEllipse(points[points.count() - 1], 2, 2);
//    }
    painter->restore();
}



#include "moc_splinechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
