#include "scatterpresenter_p.h"
#include "qscatterseries.h"
#include "scatterseries_p.h"
#include "chartpresenter_p.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QTime>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ScatterPresenter::ScatterPresenter(QScatterSeries *series, QGraphicsObject *parent) :
    ChartItem(parent),
    m_minX(0),
    m_maxX(0),
    m_minY(0),
    m_maxY(0),
    m_series(series),
    m_clippingRect()
{
    Q_ASSERT(parent);
    Q_ASSERT(series);

    m_clippingRect = parent->boundingRect();
    connect(series->d, SIGNAL(changed()), this, SLOT(handleModelChanged()));
    connect(this, SIGNAL(clicked(QPointF)), series, SIGNAL(clicked(QPointF)));
    setZValue(ChartPresenter::ScatterSeriesZValue);

    // TODO: how to draw a drop shadow?
//    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect();
//    dropShadow->setOffset(2.0);
//    dropShadow->setBlurRadius(2.0);
//    setGraphicsEffect(dropShadow);
}

void ScatterPresenter::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_minX = minX;
    m_maxX = maxX;
    m_minY = minY;
    m_maxY = maxY;
    changeGeometry();
}

void ScatterPresenter::handleGeometryChanged(const QRectF& rect)
{
    m_clippingRect = rect.translated(-rect.topLeft());
    changeGeometry();
    setPos(rect.topLeft());
}

void ScatterPresenter::handleModelChanged()
{
    // TODO: more fine grained modelChanged signaling
    changeGeometry();
}

void ScatterPresenter::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->save();
    painter->setClipRect(m_clippingRect);

    // TODO: how to draw a drop shadow?
    // Now using a custom implementation for drop shadow instead of QGraphicsDropShadowEffect.
    // It seems QGraphicsDropShadowEffect is quite heavy, at least on windows without open gl.
    QPen dropShadowPen(QColor(0, 0, 0, 70));
    dropShadowPen.setWidth(3);
    painter->setPen(dropShadowPen);
    painter->setBrush(dropShadowPen.color());
//    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(m_path.translated(2, 2));

    // Paint the shape
    // The custom settings in series override those defined by the theme
    QPen pen = m_markerPen;
    if (m_series->pen().color().isValid())
        pen = m_series->pen();
    painter->setPen(pen);
    if (m_series->brush().color().isValid())
        painter->setBrush(m_series->brush());
    else
        painter->setBrush(m_markerBrush);

    // If either pen or brush is opaque, we need to draw the polygons one-by-one
    if (painter->pen().color().alpha() < 255 || painter->brush().color().alpha() < 255) {
        foreach (QPolygonF pol, m_path.toSubpathPolygons())
            painter->drawPolygon(pol);
    } else {
        painter->drawPath(m_path);
    }

    painter->restore();
}

void ScatterPresenter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Empty implementation to grab mouse release events for this item
    Q_UNUSED(event)
}

void ScatterPresenter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF clickedPoint(
        m_minX + (event->lastPos().x() / m_clippingRect.width()) * (m_maxX-m_minX),
        m_maxY - (event->lastPos().y() / m_clippingRect.height()) * (m_maxY-m_minY));
    emit clicked(clickedPoint);
}

void ScatterPresenter::changeGeometry()
{
    if (m_clippingRect.isValid()) {
        prepareGeometryChange();
        qreal scalex = m_clippingRect.width() / (m_maxX - m_minX);
        qreal scaley = m_clippingRect.height() / (m_maxY - m_minY);

        int shape = m_series->shape();
        m_path = QPainterPath();
        m_path.setFillRule(Qt::WindingFill);
        const qreal size = m_series->size();

        foreach (QPointF point, m_series->data()) {
            // Convert relative coordinates to absolute pixel coordinates that can be used for drawing
            qreal x = point.x() * scalex - m_minX * scalex - size / 2;
            qreal y = m_clippingRect.height() - point.y() * scaley + m_minY * scaley - size / 2;

            if (x < scene()->width() && y < scene()->height()) {
                switch (shape) {
                case QScatterSeries::MarkerShapeDefault:
                    // Fallthrough, defaults to circle
                case QScatterSeries::MarkerShapeCircle:
                    m_path.addEllipse(x, y, size, size);
                    break;
                case QScatterSeries::MarkerShapeRectangle:
                    m_path.addRect(x, y, size, size);
                    break;
                case QScatterSeries::MarkerShapeRoundedRectangle:
                    m_path.addRoundedRect(x, y, size, size, size / 4.0, size / 4.0);
                    break;
                case QScatterSeries::MarkerShapeTiltedRectangle: {
                    // TODO: tilt the rectangle
                    m_path.addRect(x, y, size, size);
                    break;
                }
                case QScatterSeries::MarkerShapeTriangle: {
                    QPolygonF polygon;
                    polygon << QPointF(0.0, -size) << QPointF(size / 2.0, 0.0) << QPointF(-size / 2, 0.0);
                    // TODO: the position is not exactly right...
                    m_path.addPolygon(polygon.translated(x + size / 2.0, y + size));
                    break;
                }
                default:
                    // TODO: implement the rest of the shapes
                    Q_ASSERT(false);
                    break;
                }
            }
        }
    }
}

#include "moc_scatterpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
