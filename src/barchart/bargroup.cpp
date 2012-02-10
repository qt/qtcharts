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
    qDebug() << "BarGroup::layoutChanged";
    // Scale bars to new layout
    // Layout for bars:
    if (mModel.countRows() <= 0) {
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: BarGroup::layoutChanged called before graphics items are created!";
        return;
    }

    // TODO: better way to auto-layout?
    // Use reals for accurancy (we might get some compiler warnings... :)
    int itemCount = mModel.countColumns();
    int seriesCount = mModel.countRows();

    qreal tW = mWidth;
    qreal tH = mHeight;
    qreal tM = mMax;
    qreal scale = (tH/tM);

    qreal tC = itemCount+1;
    qreal xStepPerSeries = (tW/tC);

    // Scaling.
    int itemIndex(0);
    int labelIndex = itemCount * seriesCount;

    for (int item=0; item < itemCount; item++) {
        qreal xPos = xStepPerSeries * item + ((tW + mBarDefaultWidth*seriesCount)/(itemCount*2));
        qreal yPos = mHeight;
        for (int series = 0; series < seriesCount; series++) {
            qreal barHeight = mModel.valueAt(series, item) * scale;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            // TODO: width settable per bar?
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setColor(mColors.at(series));
            bar->setPos(xPos, yPos-barHeight); // item*posStep+startPos + series * mBarDefaultWidth, mHeight);
            itemIndex++;
            xPos += mBarDefaultWidth;
        }

        // TODO: Layout for labels, remove magic number
        xPos = xStepPerSeries * item + ((tW + mBarDefaultWidth*seriesCount)/(itemCount*2));
        BarLabel* label = reinterpret_cast<BarLabel*> (childItems().at(labelIndex));
        label->setPos(xPos, mHeight + 20);
        labelIndex++;
    }

    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
