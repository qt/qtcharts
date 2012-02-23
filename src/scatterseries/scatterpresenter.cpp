#include "scatterpresenter_p.h"
#include "qscatterseries.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
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
    // TODO: Optimization: avoid setting on every paint method call?
    // The custom settings in series override those defined by the theme
    int shape = m_series->markerShape();

    painter->save();
    painter->setClipRect(m_boundingRect);

    // Paint dropshadow
    QPen dropShadowPen(QColor(0, 0, 0, 70));
    dropShadowPen.setWidth(3);
    painter->setPen(dropShadowPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing);
    for (int i(0); i < m_scenex.count() && i < m_sceney.count(); i++) {
        if (scene()->width() > m_scenex.at(i) && scene()->height() > m_sceney.at(i))
            switch (shape) {
            case QScatterSeries::MarkerShapeDefault:
                // Fallthrough, defaults to circle
            case QScatterSeries::MarkerShapeCircle:
                painter->drawChord(m_scenex.at(i) + 2, m_sceney.at(i) + 2, 9, 9, 0, 5760);
                break;
            case QScatterSeries::MarkerShapePoint:
                //painter->drawPoint(m_scenex.at(i), m_sceney.at(i));
                break;
            case QScatterSeries::MarkerShapeRectangle:
                painter->drawRect(m_scenex.at(i) + 2, m_sceney.at(i) + 2, 8, 8);
                break;
            case QScatterSeries::MarkerShapeTiltedRectangle: {
                // TODO:
                static const QPointF points[4] = {
                    QPointF(-1.0 + m_scenex.at(i), 0.0 + m_sceney.at(i)),
                    QPointF(0.0 + m_scenex.at(i), 1.0 + m_sceney.at(i)),
                    QPointF(1.0 + m_scenex.at(i), 0.0 + m_sceney.at(i)),
                    QPointF(0.0 + m_scenex.at(i), -1.0 + m_sceney.at(i))
                };
                painter->drawPolygon(points, 4);
                break;
            }
            default:
                // TODO: implement the rest of the shapes
                Q_ASSERT(false);
                break;
            }
    }

    // Paint the shape
    QPen pen = m_markerPen;
    if (m_series->markerPen().color().isValid())
        pen = m_series->markerPen();
    if (m_series->markerBrush().color().isValid())
        painter->setBrush(m_series->markerBrush());
    else
        painter->setBrush(m_markerBrush);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, false);
    for (int i(0); i < m_scenex.count() && i < m_sceney.count(); i++) {
        if (scene()->width() > m_scenex.at(i) && scene()->height() > m_sceney.at(i))
            switch (shape) {
            case QScatterSeries::MarkerShapeDefault:
                // Fallthrough, defaults to circle
            case QScatterSeries::MarkerShapeCircle:
                painter->drawChord(m_scenex.at(i), m_sceney.at(i), 9, 9, 0, 5760);
                break;
            case QScatterSeries::MarkerShapePoint:
                painter->drawPoint(m_scenex.at(i), m_sceney.at(i));
                break;
            case QScatterSeries::MarkerShapeRectangle:
                painter->drawRect(m_scenex.at(i), m_sceney.at(i), 9, 9);
                break;
            case QScatterSeries::MarkerShapeTiltedRectangle: {
                // TODO:
                static const QPointF points[4] = {
                    QPointF(-1.0 + m_scenex.at(i), 0.0 + m_sceney.at(i)),
                    QPointF(0.0 + m_scenex.at(i), 1.0 + m_sceney.at(i)),
                    QPointF(1.0 + m_scenex.at(i), 0.0 + m_sceney.at(i)),
                    QPointF(0.0 + m_scenex.at(i), -1.0 + m_sceney.at(i))
                };
                painter->drawPolygon(points, 4);
                break;
            }
            default:
                // TODO: implement the rest of the shapes
                Q_ASSERT(false);
                break;
            }
    }

    painter->restore();
}

void ScatterPresenter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "ScatterPresenter::mousePressEvent" << event;
}

void ScatterPresenter::changeGeometry()
{
    if (m_boundingRect.isValid()) {

        prepareGeometryChange();
        qreal scalex = m_boundingRect.width() / m_visibleChartArea.spanX();
        qreal scaley = m_boundingRect.height() / m_visibleChartArea.spanY();
        m_scenex.clear();
        m_sceney.clear();

        // Convert relative coordinates to absolute pixel coordinates that can be used for drawing
        foreach (QPointF point, m_series->data()) {
            m_scenex.append(m_boundingRect.left() + point.x() * scalex - m_visibleChartArea.m_minX * scalex);
            m_sceney.append(m_boundingRect.bottom() - point.y() * scaley + m_visibleChartArea.m_minY * scaley);
        }
    }
}

#include "moc_scatterpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
