#include "legendscrollbutton_p.h"
#include "qlegend.h"
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendScrollButton::LegendScrollButton(ScrollButtonId id, QLegend *legend)
    : QGraphicsPolygonItem(legend),
    m_id(id),
    m_ledgend(legend)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

LegendScrollButton::ScrollButtonId LegendScrollButton::id()
{
    return m_id;
}

void LegendScrollButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    m_ledgend->scrollButtonClicked(this);
}

#include "moc_legendscrollbutton_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

