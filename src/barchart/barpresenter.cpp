#include "barpresenter_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarPresenter::BarPresenter(QBarSeries *series, QChart *parent) :
    BarPresenterBase(series, parent)
{
}

void BarPresenter::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries->barsetCount() <= 0) {
        qDebug() << "No sets in model!";
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: BarPresenter::layoutChanged called before graphics items are created!";
        return;
    }

    // Use temporary qreals for accurancy (we might get some compiler warnings... :)
    int categoryCount = mSeries->categoryCount();
    int setCount = mSeries->barsetCount();

    qreal tW = mWidth;
    qreal tH = mHeight;
    qreal tM = mSeries->max();
    qreal scale = (tH/tM);
    qreal tC = categoryCount + 1;
    qreal categoryWidth = tW/tC;
    mBarWidth = categoryWidth / (setCount+1);

    int itemIndex(0);
    for (int category=0; category < categoryCount; category++) {
        qreal xPos = categoryWidth * category + categoryWidth /2 + mBarWidth/2;
        qreal yPos = mHeight;
        for (int set = 0; set < setCount; set++) {
            qreal barHeight = mSeries->valueAt(set,category) * scale;
            Bar* bar = mBars.at(itemIndex);

            // TODO: width settable per bar?
            bar->resize(mBarWidth, barHeight);
            bar->setBrush(mSeries->barsetAt(set)->brush());
            bar->setPos(xPos, yPos-barHeight);
            itemIndex++;
            xPos += mBarWidth;
        }
    }

    // Position floating values
    itemIndex = 0;
    for (int category=0; category < mSeries->categoryCount(); category++) {
        qreal xPos = categoryWidth * category + categoryWidth/2 + mBarWidth;
        qreal yPos = mHeight;
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
            xPos += mBarWidth;
        }
    }
}

#include "moc_barpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
