#include "percentbargroup.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE


PercentBarGroup::PercentBarGroup(BarChartModel& model, QGraphicsItem *parent) :
    BarGroupBase(model, parent)
{
}

void PercentBarGroup::layoutChanged()
{
//    qDebug() << "PercentBarGroup::layoutChanged";
    // Scale bars to new layout
    // Layout for bars:
    if (mModel.countSets() <= 0) {
        qDebug() << "No sets in model!";
        // Nothing to do.
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: PercentBarGroup::layoutChanged called before graphics items are created!";
        return;
    }

    // TODO: better way to auto-layout
    // Use reals for accurancy (we might get some compiler warnings... :)
    int count = mModel.countCategories();
    int itemIndex(0);
    qreal tW = mWidth;
    qreal tC = count+1;
    qreal xStep = (tW/tC);
    qreal xPos = ((tW/tC) - mBarDefaultWidth / 2);
    int labelIndex = mModel.countCategories() * mModel.countSets();

    for (int category = 0; category < mModel.countCategories(); category++) {
        qreal colSum = mModel.categorySum(category);
        qreal h = mHeight;
        qreal scale = (h / colSum);
        qreal yPos = h;
        for (int set=0; set < mModel.countSets(); set++) {
            qreal barHeight = mModel.valueAt(set, category) * scale;
            Bar* bar = reinterpret_cast<Bar*> (childItems().at(itemIndex));

            // TODO: width settable per bar?
            bar->resize(mBarDefaultWidth, barHeight);
            bar->setBrush(mModel.setAt(set).brush());
            bar->setPos(xPos, yPos-barHeight);
            itemIndex++;
            yPos -= barHeight;
        }

        // TODO: Layout for labels, remove magic number
        BarLabel* label = reinterpret_cast<BarLabel*> (childItems().at(labelIndex));
        label->setPos(xPos, mHeight + 20);
        labelIndex++;
        xPos += xStep;
    }

    // Position separators
    int separatorIndex = labelIndex;    // Separators are after labels in childItems(). TODO: better way to store these?
    xPos = xStep + xStep/2;             // Initial position is between first and second group. ie one and half steps from left.
    for (int s=0; s < mModel.countCategories() - 1; s++) {
        Separator* sep = reinterpret_cast<Separator*> (childItems().at(separatorIndex));
        sep->setPos(xPos,0);
        sep->setSize(QSizeF(1,mHeight));
        xPos += xStep;
        separatorIndex++;
    }

    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
