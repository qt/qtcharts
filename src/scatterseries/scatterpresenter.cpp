#include "scatterpresenter_p.h"
#include "qscatterseries.h"
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
    m_series(series),
    m_boundingRect(),
    m_visibleChartArea()
{
    if (parent)
        m_boundingRect = parent->boundingRect();

    if (series) {
        connect(series, SIGNAL(changed()), this, SLOT(handleModelChanged()));
    }

    setZValue(ChartPresenter::ScatterSeriesZValue);

    // TODO: how to draw a drop shadow?
//    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect();
//    dropShadow->setOffset(2.0);
//    dropShadow->setBlurRadius(2.0);
//    setGraphicsEffect(dropShadow);
}

void ScatterPresenter::handleDomainChanged(const Domain& domain)
{
    m_visibleChartArea = domain;
    changeGeometry();
}

void ScatterPresenter::handleGeometryChanged(const QRectF& rect)
{
    m_boundingRect = rect.translated(-rect.topLeft());
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
    painter->setClipRect(m_boundingRect);

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
        m_visibleChartArea.m_minX + (event->lastPos().x() / m_boundingRect.width()) * m_visibleChartArea.spanX(),
        m_visibleChartArea.m_maxY - (event->lastPos().y() / m_boundingRect.height()) * m_visibleChartArea.spanY());
    emit clicked(clickedPoint);
}

void ScatterPresenter::changeGeometry()
{
    if (m_boundingRect.isValid()) {
        prepareGeometryChange();
        qreal scalex = m_boundingRect.width() / m_visibleChartArea.spanX();
        qreal scaley = m_boundingRect.height() / m_visibleChartArea.spanY();

        int shape = m_series->shape();
        m_path = QPainterPath();
        m_path.setFillRule(Qt::WindingFill);
        const qreal size = m_series->size();

        foreach (QPointF point, m_series->data()) {
            // Convert relative coordinates to absolute pixel coordinates that can be used for drawing
            qreal x = point.x() * scalex - m_visibleChartArea.m_minX * scalex - size / 2;
            qreal y = m_boundingRect.height() - point.y() * scaley + m_visibleChartArea.m_minY * scaley - size / 2;

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
                case QScatterSeries::MarkerShapeTiltedRectangle: {
                    // TODO: tilt the rectangle
                    m_path.addRect(x, y, size, size);
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
