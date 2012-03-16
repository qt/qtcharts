#include "qchartglobal.h"
#include "legendmarker_p.h"
#include <qpieslice.h>
#include <qbarset.h>
#include <qxyseries.h>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QGraphicsSimpleTextItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendMarker::LegendMarker(QSeries* series, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mPos(0,0)
    ,mSize(0,0)
    ,mBoundingRect(0,0,0,0)
    ,mMarkerBoundingRect(0,0,0,0)
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
    ,mPos(0,0)
    ,mSize(0,0)
    ,mBoundingRect(0,0,0,0)
    ,mMarkerBoundingRect(0,0,0,0)
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
    ,mPos(0,0)
    ,mSize(0,0)
    ,mBoundingRect(0,0,0,0)
    ,mMarkerBoundingRect(0,0,0,0)
    ,mSeries(series)
    ,mBarset(0)
    ,mPieslice(pieslice)
    ,mType(LegendMarkerTypePieslice)
    ,mTextItem(new QGraphicsSimpleTextItem(this))
    {
        setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    }

void LegendMarker::setPos(qreal x, qreal y)
{
    mPos = QPointF(x,y);
    layoutChanged();
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
    layoutChanged();
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

void LegendMarker::layoutChanged()
{
    QSizeF markerSize(10,10);
    qreal margin = 2;

    mSize.setHeight(markerSize.height() + 2 * margin);
    mSize.setWidth(mTextItem.boundingRect().width() + markerSize.width() + 3 * margin);

    mBoundingRect = QRectF(mPos.x(),mPos.y(),mSize.width(),mSize.height());

    mMarkerBoundingRect = QRectF(mPos.x() + margin, mPos.y() + margin, markerSize.width(),markerSize.height());

    mTextItem.setPos(mPos.x() + markerSize.width() + 2 * margin, mPos.y() + margin );
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
        QXYSeries* s = static_cast<QXYSeries*> (mSeries);
        setBrush(s->brush());
        setName(s->name());
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
