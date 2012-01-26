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
  ChartItem(parent)
  ,mSeries(series)
  ,mLayoutSet(false)
  ,mLayoutDirty(true)
  ,mBarDefaultWidth(10)
{
    dataChanged();
}


void BarGroup::setSize(const QSize& size)
{
    // TODO: refactor this
    qDebug() << "BarGroup::setSize";
    resize(size.width(),size.height());
}

void BarGroup::setPlotDomain(const PlotDomain& data)
{
    qDebug() << "BarGroup::setPlotDomain";
    // TODO:
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

int BarGroup::addColor( QColor color )
{
    int colorIndex = mColors.count();
    mColors.append(color);
    return colorIndex;
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
    if (mSeries.countSeries() <= 0) {
        // Nothing to do.
        return;
    }

    // TODO: better way to auto-layout
    int count = mSeries.countItemsInSeries();
    int posStep = (mWidth / (count+1));
    int startPos = (mWidth / (count+1)) - mSeries.countSeries() * mBarDefaultWidth /2;
    qDebug() << "startpos" << startPos;

    // Scaling.
    int itemIndex(0);
    for (int series = 0; series < mSeries.countSeries(); series++) {
        for (int item=0; item < mSeries.countItemsInSeries(); item++) {
            qDebug() << itemIndex;
            int barHeight = mSeries.valueAt(series, item) * mHeight / mMax;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            // TODO: width settable per bar?
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setColor(mColors.at(series));
            bar->setPos(item*posStep+startPos + series * mBarDefaultWidth, mHeight);
            itemIndex++;
        }
    }
    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
