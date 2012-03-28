#include "barvalue_p.h"
#include <QPainter>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarValue::BarValue(QBarSet &set, QGraphicsItem *parent)
    : QGraphicsObject(parent),
    m_BarSet(set),
    m_Xpos(0),
    m_Ypos(0),
    m_Width(0),
    m_Height(0)
{
    setVisible(false);
}

void BarValue::setValueString(QString str)
{
    m_ValueString = str;
}

QString BarValue::valueString()
{
    return m_ValueString;
}

void BarValue::setPen(const QPen pen)
{
    m_Pen = pen;
}

QPen BarValue::pen() const
{
    return m_Pen;
}

void BarValue::resize(qreal w, qreal h)
{
    m_Width = w;
    m_Height = h;
}

void BarValue::setPos(qreal x, qreal y)
{
    m_Xpos = x;
    m_Ypos = y;
}

void BarValue::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (isVisible()) {
        painter->setPen(m_Pen);
        painter->drawText(boundingRect(), m_ValueString);
    }
}

QRectF BarValue::boundingRect() const
{
    QRectF r(m_Xpos, m_Ypos, m_Width, m_Height);
    return r;
}

void BarValue::toggleVisible()
{
    setVisible(!isVisible());
}

#include "moc_barvalue_p.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
