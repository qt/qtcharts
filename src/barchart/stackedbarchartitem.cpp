#include "stackedbarchartitem_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartItem::StackedBarChartItem(QBarSeries *series, QChart *parent) :
    BarChartItem(series,parent)
{
}

StackedBarChartItem::~StackedBarChartItem()
{
}


void StackedBarChartItem::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries->barsetCount() <= 0) {
        qDebug() << "No sets in model!";
        // Nothing to do.
        return;
    }

    if (mSeries->categoryCount() == 0) {
        qDebug() << "No categories in model!";
        // Nothing to do
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: StackedBarChartItem::layoutChanged called before graphics items are created!";
        return;
    }

    // Use temporary qreals for accurancy (we might get some compiler warnings... :)
    qreal maxSum = mSeries->maxCategorySum();
    // Domain:
    if (mDomainMaxY > maxSum) {
        maxSum = mDomainMaxY;
    }

    qreal h = mHeight;
    qreal scale = (h / maxSum);
    qreal tW = mWidth;
    qreal tC = mSeries->categoryCount() + 1;
    qreal cC = mSeries->categoryCount() * 2 + 1;
    mBarWidth = tW / cC;
    qreal xStep = (tW/tC);
    qreal xPos = ((tW/tC) - mBarWidth / 2);

    int itemIndex(0);
    for (int category = 0; category < mSeries->categoryCount(); category++) {
        qreal yPos = h;
        for (int set=0; set < mSeries->barsetCount(); set++) {
            qreal barHeight = mSeries->valueAt(set, category) * scale;
            Bar* bar = mBars.at(itemIndex);

            bar->resize(mBarWidth, barHeight);
            bar->setPen(mSeries->barsetAt(set)->pen());
            bar->setBrush(mSeries->barsetAt(set)->brush());
            bar->setPos(xPos, yPos-barHeight);
            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }

    // Position floating values
    itemIndex = 0;
    xPos = (tW/tC);
    for (int category=0; category < mSeries->categoryCount(); category++) {
        qreal yPos = h;
        for (int set=0; set < mSeries->barsetCount(); set++) {
            qreal barHeight = mSeries->valueAt(set,category) * scale;
            BarValue* value = mFloatingValues.at(itemIndex);

            QBarSet* barSet = mSeries->barsetAt(set);
            value->resize(100,50);  // TODO: proper layout for this.
            value->setPos(xPos, yPos-barHeight/2);
            value->setPen(barSet->floatingValuePen());

            if (mSeries->valueAt(set,category) != 0) {
                value->setValueString(QString::number(mSeries->valueAt(set,category)));
            } else {
                value->setValueString(QString(""));
            }

            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }
}

#include "moc_stackedbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
