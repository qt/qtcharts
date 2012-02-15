#include "scatterpresenter.h"
#include "qscatterseries.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

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
    // TODO: The opacity should be user definable?
    //brush.setColor(QColor(255, 82, 0, 100));
    //if (m_series->markerPen().isValid()) {
    if (false) {
        QPen pen = painter->pen();
        QBrush brush = pen.brush();
        brush.setColor(m_series->markerPen().color());
        pen.setBrush(brush);
        pen.setWidth(4);
        painter->setPen(pen);
    }
    else {
        // TODO: fix this
        QPen pen = painter->pen();
        QBrush brush = pen.brush();
        brush.setColor(m_markerPen.color());
        pen.setBrush(brush);
        pen.setWidth(4);
        painter->setPen(pen);
    }

    for (int i(0); i < m_scenex.count() && i < m_sceney.count(); i++) {
        if (scene()->width() > m_scenex.at(i) && scene()->height() > m_sceney.at(i))
            //painter->drawArc(m_scenex.at(i), m_sceney.at(i), 2, 2, 0, 5760);
            painter->drawPoint(m_scenex.at(i), m_sceney.at(i));
    }
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

#include "moc_scatterpresenter.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
