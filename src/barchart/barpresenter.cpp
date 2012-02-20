#include "barpresenter.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarPresenter::BarPresenter(BarChartModel& model, QGraphicsItem *parent) :
    BarPresenterBase(model,parent)
{
    mBarDefaultWidth = 5;
}

void BarPresenter::layoutChanged()
{
//    qDebug() << "BarGroup::layoutChanged";
    // Scale bars to new layout
    // Layout for bars:
    if (mModel.countSets() <= 0) {
        qDebug() << "No sets in model!";
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: BarGroup::layoutChanged called before graphics items are created!";
        return;
    }

    // TODO: better way to auto-layout?
    // Use reals for accurancy (we might get some compiler warnings... :)
    int itemCount = mModel.countCategories();
    int setCount = mModel.countSets();

    qreal tW = mWidth;
    qreal tH = mHeight;
    qreal tM = mModel.max();
    qreal scale = (tH/tM);
    qreal tC = itemCount+1;
    qreal xStepPerSet = (tW/tC);

    // Scaling.
    int itemIndex(0);
    int labelIndex = itemCount * setCount;

    for (int item=0; item < itemCount; item++) {
        qreal xPos = xStepPerSet * item + ((tW + mBarDefaultWidth*setCount)/(itemCount*2));
        qreal yPos = mHeight;
        for (int set = 0; set < setCount; set++) {
            qreal barHeight = mModel.valueAt(set, item) * scale;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            // TODO: width settable per bar?
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setBrush(mModel.setAt(set).brush());
            bar->setPos(xPos, yPos-barHeight); // item*posStep+startPos + set * mBarDefaultWidth, mHeight);
            itemIndex++;
            xPos += mBarDefaultWidth;
        }

        // TODO: Layout for labels, remove magic number
        xPos = xStepPerSet * item + ((tW + mBarDefaultWidth*setCount)/(itemCount*2));
        BarLabel* label = reinterpret_cast<BarLabel*> (childItems().at(labelIndex));
        label->setPos(xPos, mHeight + 20);
        labelIndex++;
    }

    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
