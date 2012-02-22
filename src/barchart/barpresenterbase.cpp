#include "barpresenterbase.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarPresenterBase::BarPresenterBase(BarChartModel& model, QGraphicsItem *parent)
    : ChartItem(parent)
    ,mBarDefaultWidth(20) // TODO: remove hard coding, when we have layout code ready
    ,mLayoutSet(false)
    ,mLayoutDirty(true)
    ,mSeparatorsVisible(false)
    ,mModel(model)
{
    dataChanged();
}

void BarPresenterBase::setSeparatorsVisible(bool visible)
{
    mSeparatorsVisible = visible;
}

void BarPresenterBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!mLayoutSet) {
        qDebug() << "BarPresenterBase::paint called without layout set. Aborting.";
        return;
    }
//    if (mLayoutDirty) {
        // Layout or data has changed. Need to redraw.
        foreach(QGraphicsItem* i, childItems()) {
            i->paint(painter,option,widget);
        }
//    }
}

QRectF BarPresenterBase::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}

void BarPresenterBase::setBarWidth( int w )
{
    mBarDefaultWidth = w;
}

void BarPresenterBase::dataChanged()
{
    // TODO: performance optimizations. Do we really need to delete and create items every time data is changed or can we reuse them?
    qDebug() << "datachanged";
    // Delete old bars
    foreach (QGraphicsItem* item, childItems()) {
        delete item;
    }

    mBars.clear();
    mLabels.clear();
    mSeparators.clear();
    mFloatingValues.clear();

    // Create new graphic items for bars
    for (int c=0; c<mModel.countCategories(); c++) {
        for (int s=0; s<mModel.countSets(); s++) {
            QBarSet *set = mModel.setAt(s);
            Bar *bar = new Bar(this);
            childItems().append(bar);
            mBars.append(bar);
            connect(bar,SIGNAL(clicked()),set,SLOT(barClicked()));
            // TODO: should the event be passed to set or not?
            //connect(bar,SIGNAL(hoverEntered(QGraphicsSceneHoverEvent* event)),set,SLOT(barHoverEntered(QGraphicsSceneHoverEvent* event)));
            //connect(bar,SIGNAL(hoverLeaved(QGraphicsSceneHoverEvent* event)),set,SLOT(barHoverLeaved(QGraphicsSceneHoverEvent *event)));
        }
    }

    // Create labels
    int count = mModel.countCategories();
    for (int i=0; i<count; i++) {
        BarLabel* label = new BarLabel(this);
        label->set(mModel.label(i));
        childItems().append(label);
        mLabels.append(label);
    }

    // Create separators
    count = mModel.countCategories() - 1;   // There is one less separator than columns
    for (int i=0; i<count; i++) {
        Separator* sep = new Separator(this);
        sep->setColor(QColor(255,0,0,255));     // TODO: color for separations from theme
        childItems().append(sep);
        mSeparators.append(sep);
    }

    // Create floating values
    for (int category=0; category<mModel.countCategories(); category++) {
        for (int s=0; s<mModel.countSets(); s++) {
            QBarSet *set = mModel.setAt(s);
            BarValue *value = new BarValue(*set, this);
            childItems().append(value);
            mFloatingValues.append(value);
            connect(set,SIGNAL(toggleFloatingValues()),value,SLOT(toggleVisible()));
        }
    }

    // TODO: if (autolayout) { layoutChanged() } or something
    mLayoutDirty = true;
}

//handlers

void BarPresenterBase::handleModelChanged(int index)
{
//    qDebug() << "BarPresenterBase::handleModelChanged" << index;
    dataChanged();
}

void BarPresenterBase::handleDomainChanged(const Domain& domain)
{
//    qDebug() << "BarPresenterBase::handleDomainChanged";
    // TODO: Figure out the use case for this.
    // Affects the size of visible item, so layout is changed.
//    layoutChanged();
}

void BarPresenterBase::handleGeometryChanged(const QRectF& rect)
{
    mWidth = rect.width();
    mHeight = rect.height();
    layoutChanged();
    mLayoutSet = true;
    setPos(rect.topLeft());
}


void BarPresenterBase::barHoverEntered(QGraphicsSceneHoverEvent *event)
{
    //TODO: show tooltip (name of series, where bar belongs...)
}

void BarPresenterBase::barHoverLeaved(QGraphicsSceneHoverEvent *event)
{
    //TODO: hide tooltip (name of series, where bar belongs...)
}

#include "moc_barpresenterbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
