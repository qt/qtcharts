#include "qchartglobal.h"
#include "legendmarker_p.h"
#include <QPainter>
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendMarker::LegendMarker(QSeries* series, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mName("")
    ,mSeries(series)
    ,mBarset(0)
    ,mPieslice(0)
    ,mType(LegendMarkerTypeSeries)
    {
        setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    }

LegendMarker::LegendMarker(QBarSet* barset, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mName("")
    ,mSeries(0)
    ,mBarset(barset)
    ,mPieslice(0)
    ,mType(LegendMarkerTypeBarset)
    {
        setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    }

LegendMarker::LegendMarker(QPieSlice* pieslice, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mName("")
    ,mSeries(0)
    ,mBarset(0)
    ,mPieslice(pieslice)
    ,mType(LegendMarkerTypePieslice)
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

QBrush LegendMarker::brush() const
{
    return mBrush;
}

void LegendMarker::setName(const QString name)
{
    mName = name;
}

QString LegendMarker::name() const
{
    return mName;
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
    switch (mType)
    {
    case LegendMarkerTypeSeries: {

        if (event->button() == Qt::LeftButton) {
            emit clicked(mSeries);
        } else if (event->button() == Qt::RightButton) {
            emit rightClicked(mSeries);
        }
        break;
    }
    case LegendMarkerTypeBarset: {

        if (event->button() == Qt::LeftButton) {
            emit clicked(mBarset);
        } else if (event->button() == Qt::RightButton) {
            emit rightClicked(mBarset);
        }
        break;
    }

    case LegendMarkerTypePieslice: {

        if (event->button() == Qt::LeftButton) {
            emit clicked(mPieslice);
        } else if (event->button() == Qt::RightButton) {
            emit rightClicked(mPieslice);
        }
        break;
        }
    default: {
        break;
    }
    }

}

#include "moc_legendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
