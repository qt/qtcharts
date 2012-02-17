#include "pieslice.h"
#include "pieslicelabel.h"
#include "piepresenter.h"
#include "qpieseries.h"
#include "qpieslice.h"
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

PieSlice::PieSlice(QGraphicsItem* parent)
    :QGraphicsObject(parent),
    m_slicelabel(new PieSliceLabel(this)),
    m_angle(0),
    m_span(0),
    m_isExploded(false)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

PieSlice::~PieSlice()
{

}

QRectF PieSlice::boundingRect() const
{
    return m_path.boundingRect();
}

QPainterPath PieSlice::shape() const
{
    return m_path;
}

void PieSlice::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(m_path);
}

void PieSlice::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    emit hoverEnter();
}

void PieSlice::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    emit hoverLeave();
}

void PieSlice::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    emit clicked();
}

void PieSlice::setPieRect(QRectF rect)
{
    m_pieRect = rect;
}

void PieSlice::updateGeometry()
{
    prepareGeometryChange();

    // calculate center angle
    qreal centerAngle = m_angle + (m_span/2);

    // adjust rect for exploding
    QRectF rect = m_pieRect;
    rect.adjust(EXPLODE_OFFSET, EXPLODE_OFFSET, -EXPLODE_OFFSET ,-EXPLODE_OFFSET);
    if (m_isExploded) {
        QPointF d = offset((centerAngle), EXPLODE_OFFSET);
        rect.translate(d.x(), d.y());
    }

    // update slice path
    // TODO: draw the shape so that it might have a hole in the center
    QPainterPath path;
    path.moveTo(rect.center());
    path.arcTo(rect, -m_angle + 90, -m_span);
    path.closeSubpath();
    m_path = path;

    // update label position
    qreal radius = rect.height() / 2;
    QPointF edgeCenter = rect.center() + offset(centerAngle, radius + 5);
    m_slicelabel->setArmStartPoint(edgeCenter);
    m_slicelabel->setArmAngle(centerAngle);
    m_slicelabel->updateGeometry();

    //qDebug() << "PieSlice::updateGeometry" << m_slicelabel->text() << boundingRect() << m_angle << m_span;
}

void PieSlice::handleSliceDataChanged()
{
    QPieSlice *slice = qobject_cast<QPieSlice*>(sender());
    Q_ASSERT(slice);
    updateData(slice);
}

void PieSlice::updateData(const QPieSlice* sliceData)
{
    // TODO: compare what has changes to avoid unneccesary geometry updates

    m_angle = sliceData->angle();
    m_span = sliceData->span();
    m_isExploded = sliceData->isExploded();
    m_pen = sliceData->pen();
    m_brush = sliceData->brush();

    m_slicelabel->setVisible(sliceData->isLabelVisible());
    m_slicelabel->setText(sliceData->label());
    m_slicelabel->setPen(sliceData->labelPen());
    m_slicelabel->setFont(sliceData->labelFont());
    m_slicelabel->setArmLength(sliceData->labelArmLenght());

    updateGeometry();
    update();
    m_slicelabel->update();
}

#include "moc_pieslice.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
