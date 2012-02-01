#include "percentbargroup.h"
#include "bar.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PercentBarGroup::PercentBarGroup(PercentBarChartSeries& series, QGraphicsItem *parent) :
  ChartItem(parent)
  ,mSeries(series)
  ,mLayoutSet(false)
  ,mLayoutDirty(true)
  ,mBarDefaultWidth(20) // TODO: remove hard coding, when we have layout code ready
{
    dataChanged();
}


void PercentBarGroup::setSize(const QSize& size)
{
//    qDebug() << "PercentBarGroup::setSize";
    mWidth = size.width();
    mHeight = size.height();
    layoutChanged();
    mLayoutSet = true;
}

void PercentBarGroup::setPlotDomain(const PlotDomain& data)
{
    qDebug() << "PercentBarGroup::setPlotDomain";
    // TODO:
}

void PercentBarGroup::setBarWidth( int w )
{
    mBarDefaultWidth = w;
}

int PercentBarGroup::addColor( QColor color )
{
    int colorIndex = mColors.count();
    mColors.append(color);
    return colorIndex;
}

void PercentBarGroup::resetColors()
{
    mColors.clear();
}

void PercentBarGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF PercentBarGroup::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}


void PercentBarGroup::dataChanged()
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

void PercentBarGroup::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries.countRows() <= 0) {
        // Nothing to do.
        return;
    }

    // TODO: better way to auto-layout
    // Use reals for accurancy (we might get some compiler warnings... :)
    int count = mSeries.countColumns();
    int itemIndex(0);
    qreal tW = mWidth;
    qreal tC = count+1;
    qreal xStep = (tW/tC);
    qreal xPos = ((tW/tC) + mBarDefaultWidth / 2);

    for (int column = 0; column < mSeries.countColumns(); column++) {
        qreal colSum = mSeries.columnSum(column);
        qreal h = mHeight;
        qreal scale = (h / colSum);
        qreal yPos = h;
        for (int row=0; row < mSeries.countRows(); row++) {
            qreal barHeight = mSeries.valueAt(row, column) * scale;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            // TODO: width settable per bar?
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setColor(mColors.at(row));
            bar->setPos(xPos, yPos-barHeight);
            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }
    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
