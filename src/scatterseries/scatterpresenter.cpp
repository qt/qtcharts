#include "scatterpresenter_p.h"
#include "qscatterseries.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTime>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ScatterPresenter::ScatterPresenter(QScatterSeries *series, QGraphicsObject *parent) :
    ChartItem(parent),
    m_series(series),
    m_boundingRect(),
    //m_markerColor(QColor()),
//    m_markerColor(QColor(255, 0, 0)),
    m_visibleChartArea()
{
    if (parent)
        m_boundingRect = parent->boundingRect();

    if (series) {
        connect(series, SIGNAL(changed()), this, SLOT(handleModelChanged()));
    }
}

void ScatterPresenter::handleDomainChanged(const Domain& domain)
{
    m_visibleChartArea = domain;
    changeGeometry();
}

void ScatterPresenter::handleGeometryChanged(const QRectF& rect)
{
    m_boundingRect = rect;
    changeGeometry();
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

    // Paint the shape
    // The custom settings in series override those defined by the theme
    QPen pen = m_markerPen;
    if (m_series->markerPen().color().isValid())
        pen = m_series->markerPen();
    if (m_series->markerBrush().color().isValid())
        painter->setBrush(m_series->markerBrush());
    else
        painter->setBrush(m_markerBrush);
    painter->setPen(pen);
    painter->drawPath(m_path);

    // TODO: how to draw a drop shadow?
    QPen dropShadowPen(QColor(0, 0, 0, 70));
    dropShadowPen.setWidth(3);
    painter->setPen(dropShadowPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(m_path.translated(2, 2));

    painter->restore();
}

void ScatterPresenter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "ScatterPresenter::mousePressEvent" << event << " cont: "
        << m_path.contains(event->lastPos());

    if (m_path.contains(event->lastPos()))
        emit clicked();
}

void ScatterPresenter::changeGeometry()
{
    if (m_boundingRect.isValid()) {
        prepareGeometryChange();
        qreal scalex = m_boundingRect.width() / m_visibleChartArea.spanX();
        qreal scaley = m_boundingRect.height() / m_visibleChartArea.spanY();

        int shape = m_series->markerShape();
        m_path = QPainterPath();

        foreach (QPointF point, m_series->data()) {
            // Convert relative coordinates to absolute pixel coordinates that can be used for drawing
            qreal x = m_boundingRect.left() + point.x() * scalex - m_visibleChartArea.m_minX * scalex;
            qreal y = m_boundingRect.bottom() - point.y() * scaley + m_visibleChartArea.m_minY * scaley;

            if (scene()->width() > x && scene()->height() > y) {
                switch (shape) {
                case QScatterSeries::MarkerShapeDefault:
                    // Fallthrough, defaults to circle
                case QScatterSeries::MarkerShapeCircle:
                    m_path.addEllipse(x, y, 9, 9);
                    break;
                case QScatterSeries::MarkerShapePoint:
                    m_path.addEllipse(x, y, 2, 2);
                    break;
                case QScatterSeries::MarkerShapeRectangle:
                    m_path.addRect(x, y, 9, 9);
                    break;
                case QScatterSeries::MarkerShapeTiltedRectangle: {
                    // TODO:
//                    static const QPointF points[4] = {
//                        QPointF(-1.0 + x, 0.0 + y),
//                        QPointF(0.0 + x, 1.0 + y),
//                        QPointF(1.0 + x, 0.0 + y),
//                        QPointF(0.0 + x, -1.0 + y)
//                    };
                    //m_path.addPolygon(QPolygon(4, &points));
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
