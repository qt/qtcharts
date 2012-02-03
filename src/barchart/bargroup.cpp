#include "bargroup.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarGroup::BarGroup(BarChartSeries& series, QGraphicsItem *parent) :
    ChartItem(parent)
    ,mSeries(series)
    ,mBarDefaultWidth(10)
    ,mLayoutSet(false)
    ,mLayoutDirty(true)
{
    dataChanged();
}

void BarGroup::setSize(const QSizeF& size)
{
    qDebug() << "BarGroup::setSize";
    mWidth = size.width();
    mHeight = size.height();
    layoutChanged();
    mLayoutSet = true;
}

void BarGroup::setPlotDomain(const PlotDomain& data)
{
    qDebug() << "BarGroup::setPlotDomain";
    // TODO:
    mPlotDomain = data;
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

void BarGroup::resetColors()
{
    mColors.clear();
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
        mLayoutDirty = false;
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

    // TODO: labels from series. This creates just some example labels
    int count = mSeries.countColumns();
    for (int i=0; i<count; i++) {
        BarLabel* label = new BarLabel(this);
        QString text("Label " + QString::number(i));
        label->set(text);
        childItems().append(label);
    }

    // TODO: if (autolayout) { layoutChanged() } or something
    mLayoutDirty = true;
}

void BarGroup::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries.countRows() <= 0) {
        // Nothing to do.
        return;
    }

    // TODO: better way to auto-layout?
    // Use reals for accurancy (we might get some compiler warnings... :)
    int columnCount = mSeries.countColumns();
    int rowCount = mSeries.countRows();

    qreal tW = mWidth;
    qreal tH = mHeight;
    qreal tM = mMax;
    qreal scale = (tH/tM);

    qreal tC = columnCount+1;
    qreal xStepPerSeries = (tW/tC);

    // Scaling.
    int itemIndex(0);
    int labelIndex = mSeries.countColumns() * mSeries.countRows();

    for (int column=0; column < columnCount; column++) {
        qreal xPos = xStepPerSeries * column + ((tW + mBarDefaultWidth*rowCount)/(columnCount*2));
        qreal yPos = mHeight;
        for (int row = 0; row < rowCount; row++) {
            qreal barHeight = mSeries.valueAt(row, column) * scale;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            // TODO: width settable per bar?
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setColor(mColors.at(row));
            bar->setPos(xPos, yPos-barHeight); // item*posStep+startPos + series * mBarDefaultWidth, mHeight);
            itemIndex++;
            xPos += mBarDefaultWidth;
        }

        // TODO: Layout for labels, remove magic number
        xPos = xStepPerSeries * column + ((tW + mBarDefaultWidth*rowCount)/(columnCount*2));
        BarLabel* label = reinterpret_cast<BarLabel*> (childItems().at(labelIndex));
        label->setPos(xPos, mHeight + 20);
        labelIndex++;
    }

    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
