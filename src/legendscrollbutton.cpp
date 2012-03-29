#include "legendscrollbutton_p.h"
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendScrollButton::LegendScrollButton(ScrollButtonId id, QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
    ,m_id(id)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

LegendScrollButton::ScrollButtonId LegendScrollButton::id()
{
    return m_id;
}

void LegendScrollButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(event);
}

#include "moc_legendscrollbutton_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

