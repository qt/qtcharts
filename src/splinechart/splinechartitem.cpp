#include "splinechartitem_p.h"
#include "chartpresenter_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplineChartItem::SplineChartItem(QSplineSeries* series, QGraphicsItem *parent) :
XYChartItem(series, parent),
m_series(series),
m_pointsVisible(false)
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
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2*m_pointPen.width());
    update();
}

//painter

void SplineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->save();
    painter->setClipRect(clipRect());
    painter->setPen(m_linePen);
    painter->drawPath(m_path);
    if(m_pointsVisible){
           painter->setPen(m_pointPen);
           painter->drawPoints(points());
    }
    painter->restore();
}



#include "moc_splinechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
