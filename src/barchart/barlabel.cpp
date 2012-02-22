#include "barlabel_p.h"
#include <QPainter>
QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarLabel::BarLabel(QGraphicsItem* parent) : ChartItem(parent)
{
}

void BarLabel::set(QString label)
{
    mLabel = label;
}

void BarLabel::setPos(qreal x, qreal y)
{
    mXpos = x;
    mYpos = y;
}

void BarLabel::setSize(const QSizeF &size)
{
    mSize = size;
}

void BarLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawText(boundingRect(),mLabel);
}

QRectF BarLabel::boundingRect() const
{
    QRectF r(mXpos, mYpos, mSize.width(), mSize.height());
    return r;
}

QTCOMMERCIALCHART_END_NAMESPACE
