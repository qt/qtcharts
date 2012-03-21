#include "stackedbarchartitem_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartItem::StackedBarChartItem(QBarSeries *series, ChartPresenter *presenter) :
    BarChartItem(series,presenter)
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

    qreal height = geometry().height();
    qreal width = geometry().width();
    qreal scale = (height /  mSeries->maxCategorySum());
    qreal categotyCount = mSeries->categoryCount();
    qreal barWidth = width / (categotyCount *2);
    qreal xStep = width/categotyCount;
    qreal xPos = xStep/2 - barWidth/2;


    int itemIndex(0);
    for (int category = 0; category < categotyCount; category++) {
        qreal yPos = height;
        for (int set=0; set < mSeries->barsetCount(); set++) {
            qreal barHeight = mSeries->valueAt(set, category) * scale;
            Bar* bar = mBars.at(itemIndex);
            bar->setPen(mSeries->barsetAt(set)->pen());
            bar->setBrush(mSeries->barsetAt(set)->brush());
            bar->setRect(xPos, yPos-barHeight,barWidth, barHeight);
            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }

    // Position floating values
    itemIndex = 0;
    xPos = (width/categotyCount);
    for (int category=0; category < mSeries->categoryCount(); category++) {
        qreal yPos = height;
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
