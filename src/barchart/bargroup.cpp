#include "bargroup.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarGroup::BarGroup(BarChartSeries& series, QGraphicsItem *parent) :
    BarGroupBase(series,parent)
{
    mBarDefaultWidth = 10;
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
