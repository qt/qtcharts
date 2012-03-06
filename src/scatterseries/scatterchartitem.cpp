#include "scatterchartitem_p.h"
#include "qscatterseries.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QGraphicsScene>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ScatterChartItem::ScatterChartItem(QScatterSeries *series, QGraphicsObject *parent) :
    XYChartItem(series,parent),
    m_series(series),
    m_items(this),
    m_shape(QScatterSeries::MarkerShapeRectangle),
    m_size(10)

{
    Q_ASSERT(parent);
    Q_ASSERT(series);

    connect(m_series,SIGNAL(updated()), this, SLOT(handleUpdated()));

    setZValue(ChartPresenter::ScatterSeriesZValue);
    setFlags(QGraphicsItem::ItemHasNoContents);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);

    handleUpdated();

    // TODO: how to draw a drop shadow?
//    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect();
//    dropShadow->setOffset(2.0);
//    dropShadow->setBlurRadius(2.0);
//    setGraphicsEffect(dropShadow);
}


QRectF ScatterChartItem::boundingRect() const
{
    return m_rect;
}

void ScatterChartItem::createPoints(int count)
{
    for (int i = 0; i < count; ++i) {

        QGraphicsItem *item;

        switch (m_shape) {
                   case QScatterSeries::MarkerShapeDefault:
                   // Fallthrough, defaults to circle
                   case QScatterSeries::MarkerShapeCircle:
                       item = new QGraphicsEllipseItem(0,0,m_size,m_size);
                       break;
                   case QScatterSeries::MarkerShapeRectangle:
                       item = new QGraphicsRectItem(0,0,m_size,m_size);
                       break;
                   case QScatterSeries::MarkerShapeRoundedRectangle:
                       //m_path.addRoundedRect(x, y, size, size, size / 4.0, size / 4.0);
                       break;
                   case QScatterSeries::MarkerShapeTiltedRectangle:
                       // TODO: tilt the rectangle
                       //m_path.addRect(x, y, size, size);
                       //break;
                   case QScatterSeries::MarkerShapeTriangle:
                       //QPolygonF polygon;
                       //polygon << QPointF(0.0, -size) << QPointF(size / 2.0, 0.0) << QPointF(-size / 2, 0.0);
                       // TODO: the position is not exactly right...
                       //m_path.addPolygon(polygon.translated(x + size / 2.0, y + size));
                       break;
        }
        m_items.addToGroup(item);
    }
}

void ScatterChartItem::deletePoints(int count)
{
    QList<QGraphicsItem *> items = m_items.childItems();

    for (int i = 0; i < count; ++i) {
        delete(items.takeLast());
    }
}

/*

void ScatterChartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    QPointF clickedPoint(
        m_minX + (event->lastPos().x() / m_clippingRect.width()) * (m_maxX-m_minX),
        m_maxY - (event->lastPos().y() / m_clippingRect.height()) * (m_maxY-m_minY));
    emit clicked(clickedPoint);

}
*/

void ScatterChartItem::setGeometry(QVector<QPointF>& points)
{
    if(points.size()==0) return;

    int diff = XYChartItem::points().size() - points.size();

    if(diff>0) {
        deletePoints(diff);
    }
    else if(diff<0) {
        createPoints(-diff);
    }

    if(diff!=0) handleUpdated();

    QList<QGraphicsItem*> items = m_items.childItems();

    for(int i=0; i< points.size();i++) {
        QGraphicsItem* item = items.at(i);
        const QPointF& point = points.at(i);
        item->setPos(point.x()-1,point.y()-1);
        if(!clipRect().contains(point)) {
            item->setVisible(false);
        }
        else {
            item->setVisible(true);
        }
    }

    prepareGeometryChange();
    m_rect = clipRect();
    XYChartItem::setGeometry(points);
}


void ScatterChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void ScatterChartItem::setPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_items.childItems()) {
           static_cast<QAbstractGraphicsShapeItem*>(item)->setPen(pen);
    }
}

void ScatterChartItem::setBrush(const QBrush& brush)
{
    foreach(QGraphicsItem* item , m_items.childItems()) {
            static_cast<QAbstractGraphicsShapeItem*>(item)->setBrush(brush);
     }
}

void ScatterChartItem::handleUpdated()
{

    int count = m_items.childItems().count();

    if(count==0) return;

    bool recreate = m_size != m_series->size() || m_shape != m_series->shape();

    //TODO: only rewrite on size change

    m_size = m_series->size();
    m_shape = m_series->shape();

    if(recreate){
        deletePoints(count);
        createPoints(count);
    }

    setPen(m_series->pen());
    setBrush(m_series->brush());

}

#include "moc_scatterchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
