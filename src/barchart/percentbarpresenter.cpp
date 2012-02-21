#include "percentbarpresenter.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "barvalue_p.h"
#include "separator_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE


PercentBarPresenter::PercentBarPresenter(BarChartModel& model, QGraphicsItem *parent) :
    BarPresenterBase(model, parent)
{
}

void PercentBarPresenter::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mModel.countSets() <= 0) {
        qDebug() << "No sets in model!";
        // Nothing to do.
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: PercentBarPresenter::layoutChanged called before graphics items are created!";
        return;
    }

    // TODO: better way to auto-layout
    // Use reals for accurancy (we might get some compiler warnings... :)
    int count = mModel.countCategories();
    int itemIndex(0);
    int labelIndex(0);
    qreal tW = mWidth;
    qreal tC = count+1;
    qreal xStep = (tW/tC);
    qreal xPos = ((tW/tC) - mBarDefaultWidth / 2);
    qreal h = mHeight;

    for (int category = 0; category < mModel.countCategories(); category++) {
        qreal colSum = mModel.categorySum(category);
        qreal scale = (h / colSum);
        qreal yPos = h;
        for (int set=0; set < mModel.countSets(); set++) {
            qreal barHeight = mModel.valueAt(set, category) * scale;
            Bar* bar = mBars.at(itemIndex);

            // TODO: width settable per bar?
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
    xPos = xStep + xStep/2;
    for (int s=0; s < mModel.countCategories() - 1; s++) {
        Separator* sep = mSeparators.at(s);
        sep->setPos(xPos,0);
        sep->setSize(QSizeF(1,mHeight));
        xPos += xStep;
    }

    // Position floating values
    itemIndex = 0;
    xPos = ((tW/tC) - mBarDefaultWidth / 2);
    for (int category=0; category < mModel.countCategories(); category++) {
        qreal yPos = h;
        qreal colSum = mModel.categorySum(category);
        qreal scale = (h / colSum);
        for (int set=0; set < mModel.countSets(); set++) {
            qreal barHeight = mModel.valueAt(set,category) * scale;
            BarValue* value = mFloatingValues.at(itemIndex);

            // TODO: remove hard coding, apply layout
            value->setPos(xPos + mBarDefaultWidth/2, yPos-barHeight/2);
            value->setPen(QPen(QColor(255,255,255,255)));

            QString vString(QString::number(mModel.percentageAt(set,category) * 100));
            vString.append("%");
            value->setValueString(vString);

            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }

    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
