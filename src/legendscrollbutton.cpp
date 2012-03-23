#include "legendscrollbutton_p.h"
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendScrollButton::LegendScrollButton(ScrollButtonId id, QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
    ,mId(id)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

LegendScrollButton::ScrollButtonId LegendScrollButton::id()
{
    return mId;
}

void LegendScrollButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(event);
}

#include "moc_legendscrollbutton_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

