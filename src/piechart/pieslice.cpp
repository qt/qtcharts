#include "pieslice.h"
#include "piepresenter.h"
#include "qpieseries.h"
#include <QPainter>
#include <QDebug>
#include <qmath.h>
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#define PI 3.14159265
#define EXPLODE_OFFSET 20

QPointF offset(qreal angle, qreal length)
{
    qreal dx = qSin(angle*(PI/180)) * length;
    qreal dy = qCos(angle*(PI/180)) * length;
    return QPointF(dx, -dy);
}

PieSlice::PieSlice(PiePresenter *presenter, int seriesIndex, qreal startAngle, qreal span)
    :QGraphicsItem(presenter),
    m_label(new QGraphicsTextItem(this)),
    m_seriesIndex(seriesIndex),
    m_startAngle(startAngle),
    m_span(span)
{
    Q_ASSERT(presenter);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    updateGeometry();

    // TODO: use themes
    m_pen = QPen(Qt::black);
    m_brush = QBrush(sliceData().m_color);
}

PieSlice::~PieSlice()
{
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
    painter->setRenderHint(QPainter::Antialiasing);

    // TODO: themes
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(m_path);

    // Draw the label
    // TODO: do this better
    //QTextItem text;
    painter->drawText(m_center, sliceData().m_label);
}

void PieSlice::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    m_brush = QBrush(sliceData().m_color.lighter());
    update();
}

void PieSlice::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    m_brush = QBrush(sliceData().m_color);
    update();
}

void PieSlice::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    QPieSlice data = sliceData();
    data.m_isExploded = !data.m_isExploded;
    (static_cast<PiePresenter*>(parentItem()))->m_pieSeries->update(m_seriesIndex, data);
}

void PieSlice::updateGeometry()
{
    prepareGeometryChange();

    PiePresenter *presenter = static_cast<PiePresenter*>(parentItem());
    QRectF rect = presenter->pieRect();
    rect.adjust(EXPLODE_OFFSET, EXPLODE_OFFSET, -EXPLODE_OFFSET ,-EXPLODE_OFFSET);

    qreal centerAngle = m_startAngle + (m_span/2);

    if (presenter->m_pieSeries->slice(m_seriesIndex).m_isExploded) {
        QPointF d = offset((centerAngle), EXPLODE_OFFSET);
        rect.translate(d.x(), d.y());
    }

    qreal angle = (-m_startAngle) + (90);
    qreal span = -m_span;

    QPainterPath path;
    path.moveTo(rect.center());
    path.arcTo(rect, angle, span);

    // TODO: draw the shape so that it might have a hole in the center

    m_path = path;
    m_rect = path.boundingRect();

    qreal radius = rect.height() / 2;
    m_center = rect.center() + offset(centerAngle, radius / 2);
}

QPieSlice PieSlice::sliceData()
{
    return (static_cast<PiePresenter*>(parentItem()))->m_pieSeries->slice(m_seriesIndex);
}

QTCOMMERCIALCHART_END_NAMESPACE
