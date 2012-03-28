#include "barvalue_p.h"
#include <QPainter>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarValue::BarValue(QBarSet &set, QGraphicsItem *parent)
    : QGraphicsObject(parent),
    m_barSet(set),
    m_xPos(0),
    m_yPos(0),
    m_width(0),
    m_height(0)
{
    setVisible(false);
}

void BarValue::setValueString(QString str)
{
    m_valueString = str;
}

QString BarValue::valueString()
{
    return m_valueString;
}

void BarValue::setPen(const QPen pen)
{
    m_pen = pen;
}

QPen BarValue::pen() const
{
    return m_pen;
}

void BarValue::resize(qreal w, qreal h)
{
    m_width = w;
    m_height = h;
}

void BarValue::setPos(qreal x, qreal y)
{
    m_xPos = x;
    m_yPos = y;
}

void BarValue::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (isVisible()) {
        painter->setPen(m_pen);
        painter->drawText(boundingRect(), m_valueString);
    }
}

QRectF BarValue::boundingRect() const
{
    QRectF r(m_xPos, m_yPos, m_width, m_height);
    return r;
}

void BarValue::toggleVisible()
{
    setVisible(!isVisible());
}

#include "moc_barvalue_p.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
