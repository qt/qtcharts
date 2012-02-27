#include "scatterpresenter_p.h"
#include "qscatterseries.h"
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

    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect();
    dropShadow->setOffset(2.0);
    dropShadow->setBlurRadius(2.0);
    setGraphicsEffect(dropShadow);
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
    if (m_series->pen().color().isValid())
        pen = m_series->pen();
    if (m_series->brush().color().isValid())
        painter->setBrush(m_series->brush());
    else
        painter->setBrush(m_markerBrush);
    painter->setPen(pen);
    painter->drawPath(m_path);

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

        int shape = m_series->shape();
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
                    // TODO: tilt the rectangle
                    m_path.addRect(x, y, 9, 9);
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
