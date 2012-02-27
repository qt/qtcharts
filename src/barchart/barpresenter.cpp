#include "barpresenter.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarPresenter::BarPresenter(QBarSeries *series, QGraphicsItem *parent) :
    BarPresenterBase(series, parent)
{
    mBarDefaultWidth = 15;
}

void BarPresenter::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries->countSets() <= 0) {
        qDebug() << "No sets in model!";
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: BarPresenter::layoutChanged called before graphics items are created!";
        return;
    }

    // TODO: better way to auto-layout?
    // Use reals for accurancy (we might get some compiler warnings... :)
    int categoryCount = mSeries->countCategories();
    int setCount = mSeries->countSets();

    qreal tW = mWidth;
    qreal tH = mHeight;
    qreal tM = mSeries->max();
    qreal scale = (tH/tM);
    qreal tC = categoryCount+1;
    qreal xStepPerSet = (tW/tC);

    // Scaling.
    int itemIndex(0);
    int labelIndex(0);

    for (int category=0; category < categoryCount; category++) {
        qreal xPos = xStepPerSet * category + ((tW + mBarDefaultWidth*setCount)/(categoryCount*2));
        qreal yPos = mHeight;
        for (int set = 0; set < setCount; set++) {
            qreal barHeight = mSeries->valueAt(set,category) * scale;
            Bar* bar = mBars.at(itemIndex);

            // TODO: width settable per bar?
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setBrush(mSeries->setAt(set)->brush());
            bar->setPos(xPos, yPos-barHeight);
            itemIndex++;
            xPos += mBarDefaultWidth;
        }

        // TODO: Layout for labels, remove magic number
        xPos = xStepPerSet * category + ((tW + mBarDefaultWidth*setCount)/(categoryCount*2));
        BarLabel* label = mLabels.at(labelIndex);
        label->setPos(xPos, mHeight + 20);
        labelIndex++;
    }

    // Position floating values
    itemIndex = 0;
    for (int category=0; category < mSeries->countCategories(); category++) {
        qreal xPos = xStepPerSet * category + ((tW + mBarDefaultWidth*setCount)/(categoryCount*2));
        qreal yPos = mHeight;
        for (int set=0; set < mSeries->countSets(); set++) {
            qreal barHeight = mSeries->valueAt(set,category) * scale;
            BarValue* value = mFloatingValues.at(itemIndex);

            // TODO: remove hard coding, apply layout
            value->resize(100,50);
            value->setPos(xPos, yPos-barHeight/2);
            value->setPen(QPen(QColor(255,255,255,255)));

            if (mSeries->valueAt(set,category) != 0) {
                value->setValueString(QString::number(mSeries->valueAt(set,category)));
            } else {
                value->setValueString(QString(""));
            }

            itemIndex++;
            xPos += mBarDefaultWidth;
        }
    }
    mLayoutDirty = true;
}

#include "moc_barpresenter.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
