#include "pieslice.h"
#include "piepresenter.h"
#include <QPainter>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieSlice::PieSlice(PiePresenter *piePresentation, int seriesIndex, qreal startAngle, qreal span)
    :QGraphicsItem(piePresentation),
    m_seriesIndex(seriesIndex),
    m_startAngle(startAngle),
    m_span(span)
{
    Q_ASSERT(piePresentation);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

PieSlice::~PieSlice()
{
}

QRectF PieSlice::boundingRect() const
{
    return shape().boundingRect();
}

QPainterPath PieSlice::shape() const
{
    QRectF rect = (static_cast<PiePresenter*>(parentItem()))->pieRect();
    qreal angle = (-m_startAngle) + (90);
    qreal span = -m_span;

    QPainterPath path;
    path.moveTo(rect.center());
    path.arcTo(rect, angle, span);

    // TODO: draw the shape so that it might have a hole in the center
    // - Sin & Cos will be needed to find inner/outer arc endpoints

    // dx, dy are offsets from the center
    //qreal l = boundingRect().height();
    //qreal dx = qSin(angle*(M_PI/180)) * l;
    //qreal dy = qCos(angle*(M_PI/180)) * l;

    // TODO: exploded slice?

    return path;
}

void PieSlice::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setRenderHint(QPainter::Antialiasing);
    // TODO: how to map theme settings to a pie slice? Now we
    //painter->setPen(m_theme.linePen);
    // TODO:

    QPieSlice data = (static_cast<PiePresenter*>(parentItem()))->m_pieSeries->slice(m_seriesIndex);
    painter->setBrush(data.m_color);


    //painter->setBrush(m_theme.linePen.color());

    // From Qt docs:
    // The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).
    // Positive values for the angles mean counter-clockwise while negative values mean the clockwise direction.
    // Zero degrees is at the 3 o'clock position.
    //
    // For sake of simplicity convert this so that zero degrees is at 12 o'clock and full circle is 360.
    //qreal angle = (-m_startAngle*16) + (90*16);
    //qreal span = -m_span*16;
    //painter->drawPie(boundingRect(), angle, span);

    painter->drawPath(shape());

    // Draw the label
    // TODO: do this better
    painter->drawText(boundingRect().center(), data.m_label);
}

void PieSlice::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    QGraphicsItem::hoverEnterEvent(event);
    qDebug() << "hover" << m_seriesIndex << m_startAngle << m_span;
}

void PieSlice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}
QTCOMMERCIALCHART_END_NAMESPACE
