#include "qchartglobal.h"
#include "legendmarker_p.h"
#include <qpieslice.h>
#include <qbarset.h>
#include <QPainter>
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendMarker::LegendMarker(QSeries* series, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mMarkerBoundingRect(0,0,1,1)
    ,mSeries(series)
    ,mBarset(0)
    ,mPieslice(0)
    ,mType(LegendMarkerTypeSeries)
    ,mTextItem(new QGraphicsSimpleTextItem(this))
    {
        setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    }

LegendMarker::LegendMarker(QSeries *series, QBarSet *barset, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mMarkerBoundingRect(0,0,1,1)
    ,mSeries(series)
    ,mBarset(barset)
    ,mPieslice(0)
    ,mType(LegendMarkerTypeBarset)
    ,mTextItem(new QGraphicsSimpleTextItem(this))
    {
        setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    }

LegendMarker::LegendMarker(QSeries *series, QPieSlice *pieslice, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mMarkerBoundingRect(0,0,1,1)
    ,mSeries(series)
    ,mBarset(0)
    ,mPieslice(pieslice)
    ,mType(LegendMarkerTypePieslice)
    ,mTextItem(new QGraphicsSimpleTextItem(this))
    {
        setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    }

void LegendMarker::setBoundingRect(const QRectF rect)
{
    mBoundingRect = rect;
    // Calculate Marker pos

    // TODO: remove hard coding. 5 is marigin around marker
    QSizeF markerSize(10,10);
    qreal x = mBoundingRect.x() + 5;
    qreal y = mBoundingRect.y() + (mBoundingRect.height() - markerSize.height())/2;
    mMarkerBoundingRect = QRectF(x,y,markerSize.width(),markerSize.height());

    mTextItem.setPos(mBoundingRect.x() + markerSize.width() + 10, y );
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
    mTextItem.setText(name);
}

QString LegendMarker::name() const
{
    return mTextItem.text();
}

QSeries* LegendMarker::series() const
{
    return mSeries;
}

void LegendMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(mBrush);
    painter->drawRect(mMarkerBoundingRect);
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
        emit clicked(mSeries,event->button());
        break;
        }
    case LegendMarkerTypeBarset: {
        emit clicked(mBarset,event->button());
        break;
        }
    case LegendMarkerTypePieslice: {
        emit clicked(mPieslice,event->button());
        break;
        }
    default: {
        break;
        }
    }
}

void LegendMarker::changed()
{
    switch (mType)
    {
    case LegendMarkerTypeSeries: {
        // TODO:
        break;
    }
    case LegendMarkerTypeBarset: {
        setBrush(mBarset->brush());
        setName(mBarset->name());
        break;
    }
    case LegendMarkerTypePieslice: {
        setBrush(mPieslice->sliceBrush());
        setName(mPieslice->label());
        break;
    }
    }
}

#include "moc_legendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
