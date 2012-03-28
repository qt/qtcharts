#include "bar_p.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Bar::Bar(QString category, QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
    m_Category(category)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    setAcceptHoverEvents(true);
}

void Bar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(m_Category);
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(m_Category);
    }
}

void Bar::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEntered(event->lastScreenPos());
}

void Bar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    emit hoverLeaved();
}

#include "moc_bar_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
