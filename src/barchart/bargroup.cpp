#include "bargroup.h"
#include "bar.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// TODO: singleton?
//BarGroup* BarGroup::mBarGroupInstance = NULL;

//BarGroup::BarGroup(QGraphicsItem *parent) :
//    QGraphicsItem(parent)
//    ,mSeries(series)
BarGroup::BarGroup(BarChartSeries& series, QGraphicsItem *parent) :
  QGraphicsItem(parent)
  ,mSeries(series)
  ,mLayoutSet(false)
  ,mLayoutDirty(true)
{
    dataChanged();
}

void BarGroup::resize( int w, int h )
{
    qDebug() << "QBarChart::resize";
    mWidth = w;
    mHeight = h;
    layoutChanged();
    mLayoutSet = true;
}

void BarGroup::setBarWidth( int w )
{
    mBarDefaultWidth = w;
}

void BarGroup::setColor( QColor color )
{
    mColor = color;
}

void BarGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!mLayoutSet) {
        qDebug() << "QBarChart::paint called without layout set. Aborting.";
        return;
    }
    if (mLayoutDirty) {
        // Layout or data has changed. Need to redraw.
        foreach(QGraphicsItem* i, childItems()) {
            i->paint(painter,option,widget);
        }
    }
}

QRectF BarGroup::boundingRect() const
{
    // TODO: correct this (currently ignores position)
    return QRectF(0,0,mWidth,mHeight);
}


void BarGroup::dataChanged()
{
    qDebug() << "QBarChart::dataChanged mSeries";

    // Find out maximum and minimum of all series
    mMax = mSeries.max();
    mMin = mSeries.min();

    // Delete old bars
    // Is this correct way to delete childItems?
    foreach (QGraphicsItem* item, childItems()) {
        delete item;
    }

    // Create new graphic items for bars
    int totalItems = mSeries.countTotalItems();
    for (int i=0; i<totalItems; i++) {
        Bar *bar = new Bar(this);
        childItems().append(bar);
    }

    mLayoutDirty = true;
}

void BarGroup::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    int count = mSeries.countSeries();
    if (count <= 0) {
        // Nothing to do.
        return;
    }

    // Align center
    int posStep = (mWidth / (count));
    int startPos = (mWidth / count+1);
    qDebug() << "startpos" << startPos;

    // Scaling. TODO: better one.
    int itemIndex(0);
    for (int series = 0; series < count; series++) {
        for (int item=0; item < count; item++) {
            int barHeight = mSeries.valueAt(series, item) * mHeight / mMax;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            bar->resize(mBarDefaultWidth, barHeight);        // TODO: width settable per bar
            bar->setColor(mColor);
            bar->setPos(itemIndex*posStep+startPos, 0);
            itemIndex++;
        }
    }
    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
