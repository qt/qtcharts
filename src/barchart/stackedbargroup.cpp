#include "stackedbargroup.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include <QDebug>
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarGroup::StackedBarGroup(StackedBarChartSeries& series, QGraphicsItem *parent) :
  ChartItem(parent)
  ,mSeries(series)
  ,mLayoutSet(false)
  ,mLayoutDirty(true)
  ,mBarDefaultWidth(20) // TODO: remove hard coding, when we have layout code ready
  ,mTheme(0)
  ,mSeparatorsVisible(true)
{
    dataChanged();
}

void StackedBarGroup::setSeparatorsVisible(bool visible)
{
    mSeparatorsVisible = visible;
}

void StackedBarGroup::setSize(const QSizeF& size)
{
    mWidth = size.width();
    mHeight = size.height();
    layoutChanged();
    mLayoutSet = true;
}

void StackedBarGroup::setPlotDomain(const PlotDomain& data)
{
    qDebug() << "StackedBarGroup::setPlotDomain";
    // TODO:
}

void StackedBarGroup::themeChanged(ChartTheme *theme)
{
    mTheme = theme;
}

void StackedBarGroup::setBarWidth( int w )
{
    mBarDefaultWidth = w;
}

int StackedBarGroup::addColor( QColor color )
{
    int colorIndex = mColors.count();
    mColors.append(color);
    return colorIndex;
}

void StackedBarGroup::resetColors()
{
    mColors.clear();
}

void StackedBarGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
        if (mSeparatorsVisible) {
            //TODO: own class for separators (graphicsitem), because they may have style etc later.
            // this is just to see that the positions are calculated correctly.
            QPen pen(QColor(0,0,255,255));
            painter->setPen(pen);
            for (int i=0; i<mSeparatorPositions.count(); i++ ) {
                qreal xp = mSeparatorPositions.at(i);
                painter->drawLine(xp,0,xp,mHeight);
            }
        }
//        mLayoutDirty = false;
    }

}

QRectF StackedBarGroup::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}


void StackedBarGroup::dataChanged()
{
    qDebug() << "QBarChart::dataChanged";

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

    // TODO: labels from series. This creates just some example labels
    int count = mSeries.countColumns();
    for (int i=0; i<count; i++) {
        BarLabel* label = new BarLabel(this);
        QString text("Label " + QString::number(i));
        label->set(text);
        childItems().append(label);
    }

    mSeparatorPositions.clear();

    // TODO: if (autolayout) { layoutChanged() } or something
    mLayoutDirty = true;
}

void StackedBarGroup::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries.countRows() <= 0) {
        // Nothing to do.
        return;
    }

    if (mSeries.countColumns() == 0) {
        // Nothing to do
        return;
    }

    // TODO: better way to auto-layout
    // Use reals for accurancy (we might get some compiler warnings... :)
    // TODO: use temp variable for column count...
    qreal maxSum = mSeries.maxColumnSum();
    qreal h = mHeight;
    qreal scale = (h / maxSum);

    int itemIndex(0);
    qreal tW = mWidth;
    qreal tC = mSeries.countColumns() + 1;
    qreal xStep = (tW/tC);
    qreal xPos = ((tW/tC) - mBarDefaultWidth / 2);
    int labelIndex = mSeries.countColumns() * mSeries.countRows();

    for (int column = 0; column < mSeries.countColumns(); column++) {
        qreal yPos = h;
        for (int row=0; row < mSeries.countRows(); row++) {
            qreal barHeight = mSeries.valueAt(row, column) * scale;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            // TODO: width settable per bar?
            // TODO: how to get color for series(x) from theme?
//            mTheme->themeForSeries();
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setColor(mColors.at(row));
            bar->setPos(xPos, yPos-barHeight);
            itemIndex++;
            yPos -= barHeight;
        }

        // TODO: Layout for labels, remove magic number
        BarLabel* label = reinterpret_cast<BarLabel*> (childItems().at(labelIndex));
        label->setPos(xPos, mHeight + 20);
        labelIndex++;
        xPos += xStep;
    }

    // Position separators
    mSeparatorPositions.clear();
    xPos = xStep + xStep/2;     // Initial position is between first and second group. ie one and half steps from left.
    for (int s=0; s < mSeries.countColumns() - 1; s++) {
        mSeparatorPositions.append(xPos);
        xPos += xStep;
    }

    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
