#include "pieslice.h"
#include "pieslicelabel.h"
#include "piepresenter.h"
#include "qpieseries.h"
#include <QPainter>
#include <QDebug>
#include <qmath.h>
#include <QGraphicsSceneEvent>
#include <QTime>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#define PI 3.14159265
#define EXPLODE_OFFSET 20

QPointF offset(qreal angle, qreal length)
{
    qreal dx = qSin(angle*(PI/180)) * length;
    qreal dy = qCos(angle*(PI/180)) * length;
    return QPointF(dx, -dy);
}

PieSlice::PieSlice(QPieSliceId id, QPieSeries *series, QGraphicsItem* parent)
    :QGraphicsObject(parent),
    m_id(id),
    m_series(series),
    m_slicelabel(new PieSliceLabel(this)),
    m_isHovering(false)
{
    Q_ASSERT(series);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    updateData();
}

PieSlice::~PieSlice()
{
    qDebug() << "~PieSlice()" << m_id;
}

QRectF PieSlice::boundingRect() const
{
    return m_rect;
}

QPainterPath PieSlice::shape() const
{
    return m_path;
}

void PieSlice::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    // set hover brush
    // TODO: what if we are using gradients...
    QBrush brush = m_data.brush();
    if (m_isHovering)
        brush.setColor(brush.color().lighter());

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_data.pen());
    painter->setBrush(brush);
    painter->drawPath(m_path);
}

void PieSlice::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    m_isHovering = true;
    update();
    // TODO: emit hoverEnter()
}

void PieSlice::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    m_isHovering = false;
    update();
    // TODO: emit hoverLeave()
}

void PieSlice::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    // TODO: emit clicked
    // TODO: should we let the user decide if this can be exploded?
    m_data.setExploded(!m_data.isExploded());
    m_series->update(m_data);
}

void PieSlice::updateGeometry(QRectF rect, qreal startAngle, qreal span)
{
    prepareGeometryChange();

    // calculate center angle
    qreal centerAngle = startAngle + (span/2);

    // adjust rect for exploding
    rect.adjust(EXPLODE_OFFSET, EXPLODE_OFFSET, -EXPLODE_OFFSET ,-EXPLODE_OFFSET);
    if (m_data.isExploded()) {
        QPointF d = offset((centerAngle), EXPLODE_OFFSET);
        rect.translate(d.x(), d.y());
    }

    // update slice path
    // TODO: draw the shape so that it might have a hole in the center
    QPainterPath path;
    path.moveTo(rect.center());
    path.arcTo(rect, -startAngle + 90, -span);
    m_path = path;
    m_rect = path.boundingRect();

    // update label position
    qreal radius = rect.height() / 2;
    QPointF edgeCenter = rect.center() + offset(centerAngle, radius + 5);
    m_slicelabel->updateGeometry(edgeCenter, centerAngle, 50);

    //qDebug() << "PieSlice::updateGeometry" << m_rect;
}

void PieSlice::updateData()
{
    if (!m_series->m_slices.contains(m_id))
        qWarning() << "PieSlice::updateData(): cannot find slice data!" << m_id;

    QPieSlice data = m_series->slice(m_id);
    // TODO: find out what has changed and trigger some animation
    m_data = data;

    update();

    m_slicelabel->setLabel(m_data.label());
    m_slicelabel->setVisible(m_data.isLabelVisible());
    m_slicelabel->update();
}

#include "moc_pieslice.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
