#include "barvalue_p.h"
#include <QPainter>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarValue::BarValue(QBarSet &set, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    ,mBarSet(set)
{
//    setVisible(false);
}

void BarValue::setValueString(QString str)
{
    mValueString = str;
}

QString BarValue::valueString()
{
    return mValueString;
}

void BarValue::setPen(const QPen& pen)
{
    mPen = pen;
}

const QPen& BarValue::pen()
{
    return mPen;
}

void BarValue::resize(qreal w, qreal h)
{
    mWidth = w;
    mHeight = h;
}

void BarValue::setPos(qreal x, qreal y)
{
    mXpos = x;
    mYpos = y;
}

bool BarValue::belongsToSet(QBarSet *set)
{
    return (&mBarSet == set);
}

void BarValue::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(mPen);
    painter->drawText(boundingRect(),mValueString);
}

QRectF BarValue::boundingRect() const
{
    QRectF r(mXpos, mYpos, mXpos + mWidth, mYpos + mHeight);
    return r;
}


QTCOMMERCIALCHART_END_NAMESPACE
