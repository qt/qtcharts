#include "stackedbarpresenter.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarPresenter::StackedBarPresenter(BarChartModel& model, QGraphicsItem *parent) :
    BarPresenterBase(model,parent)
{
}

void StackedBarPresenter::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mModel.countSets() <= 0) {
        qDebug() << "No sets in model!";
        // Nothing to do.
        return;
    }

    if (mModel.countCategories() == 0) {
        qDebug() << "No categories in model!";
        // Nothing to do
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: StackedBarPresenter::layoutChanged called before graphics items are created!";
        return;
    }

    // TODO: better way to auto-layout
    // Use reals for accurancy (we might get some compiler warnings... :)
    // TODO: use temp variable for category count...
    qreal maxSum = mModel.maxCategorySum();
    qreal h = mHeight;
    qreal scale = (h / maxSum);

    int itemIndex(0);
    int labelIndex(0);
    qreal tW = mWidth;
    qreal tC = mModel.countCategories() + 1;
    qreal xStep = (tW/tC);
    qreal xPos = ((tW/tC) - mBarDefaultWidth / 2);

    for (int category = 0; category < mModel.countCategories(); category++) {
        qreal yPos = h;
        for (int set=0; set < mModel.countSets(); set++) {
            qreal barHeight = mModel.valueAt(set, category) * scale;
            Bar* bar = mBars.at(itemIndex);

            bar->resize(mBarDefaultWidth, barHeight);
            bar->setBrush(mModel.setAt(set).brush());
            bar->setPos(xPos, yPos-barHeight);
            itemIndex++;
            yPos -= barHeight;
        }

        // TODO: Layout for labels, remove magic number
        BarLabel* label = mLabels.at(labelIndex);
        label->setPos(xPos, mHeight + 20);
        labelIndex++;
        xPos += xStep;
    }

    // Position separators
    int separatorIndex(0);
    xPos = xStep + xStep/2;
    for (int s=0; s < mModel.countCategories() - 1; s++) {
        Separator* sep = mSeparators.at(separatorIndex);
        sep->setPos(xPos,0);
        sep->setSize(QSizeF(1,mHeight));
        xPos += xStep;
        separatorIndex++;
    }

    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
