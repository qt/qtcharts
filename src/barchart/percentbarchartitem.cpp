#include "percentbarchartitem_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PercentBarChartItem::PercentBarChartItem(QBarSeries *series, ChartPresenter* presenter) :
    BarChartItem(series, presenter)
{
}

void PercentBarChartItem::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries->barsetCount() <= 0) {
        qDebug() << "No sets in model!";
        // Nothing to do.
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: PercentBarChartItem::layoutChanged called before graphics items are created!";
        return;
    }

    // Use temporary qreals for accurancy (we might get some compiler warnings... :)
    qreal width = geometry().width();
    qreal height = geometry().height();

    qreal categoryCount = mSeries->categoryCount();
    qreal barWidth = width / (mSeries->categoryCount() * 2);
    qreal xStep = width/categoryCount;
    qreal xPos =  xStep/2 - barWidth / 2;

    int itemIndex(0);
    for (int category = 0; category < categoryCount ; category++) {
        qreal colSum = mSeries->categorySum(category);
        qreal scale = (height / colSum);
        qreal yPos = height;
        for (int set=0; set < mSeries->barsetCount(); set++) {
            qreal barHeight = mSeries->valueAt(set, category) * scale;
            Bar* bar = mBars.at(itemIndex);

            // TODO: width settable per bar?

            bar->setPen(mSeries->barsetAt(set)->pen());
            bar->setRect(xPos, yPos-barHeight,barWidth, barHeight);
            bar->setBrush(mSeries->barsetAt(set)->brush());

            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }

    // Position floating values
    itemIndex = 0;
    xPos = (width/categoryCount);
    for (int category=0; category < mSeries->categoryCount(); category++) {
        qreal yPos = height;
        qreal colSum = mSeries->categorySum(category);
        qreal scale = (height / colSum);
        for (int set=0; set < mSeries->barsetCount(); set++) {
            qreal barHeight = mSeries->valueAt(set,category) * scale;
            BarValue* value = mFloatingValues.at(itemIndex);

            QBarSet* barSet = mSeries->barsetAt(set);
            value->resize(100,50);  // TODO: proper layout for this.
            value->setPos(xPos, yPos-barHeight/2);
            value->setPen(barSet->floatingValuePen());

            if (mSeries->valueAt(set,category) != 0) {
                int p = mSeries->percentageAt(set,category) * 100;
                QString vString(QString::number(p));
                vString.truncate(3);
                vString.append("%");
                value->setValueString(vString);
            } else {
                value->setValueString(QString(""));
            }

            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }
}

#include "moc_percentbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
