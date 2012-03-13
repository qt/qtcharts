#include "qchartglobal.h"
#include "legendmarker_p.h"
#include <QPainter>
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendMarker::LegendMarker(QSeries* series, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mSeries(series)
    ,mBoundingRect(0,0,1,1)
    {
        setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    }

void LegendMarker::setBoundingRect(const QRectF rect)
{
    mBoundingRect = rect;
}

void LegendMarker::setBrush(const QBrush brush)
{
    mBrush = brush;
}

void LegendMarker::setName(const QString name)
{
    mName = name;
}

QString LegendMarker::name() const
{
    return mName;
}

QColor LegendMarker::color() const
{
    return mBrush.color();
}

void LegendMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(mBrush);
    painter->drawRect(mBoundingRect);
}

QRectF LegendMarker::boundingRect() const
{
    return mBoundingRect;
}

void LegendMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(mSeries, mName);
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(mSeries, mName);
    }
}

#include "moc_legendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
