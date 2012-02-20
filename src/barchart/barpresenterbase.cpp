#include "barpresenterbase.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarPresenterBase::BarPresenterBase(BarChartModel& model, QGraphicsItem *parent)
    : ChartItem(parent)
    ,mBarDefaultWidth(20) // TODO: remove hard coding, when we have layout code ready
    ,mLayoutSet(false)
    ,mLayoutDirty(true)
    ,mSeparatorsVisible(true)
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
//    qDebug() << "BarGroupBase::paint" << childItems().count();
    if (!mLayoutSet) {
        qDebug() << "BarGroupBase::paint called without layout set. Aborting.";
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

    // Delete old bars
    foreach (QGraphicsItem* item, childItems()) {
        delete item;
    }

    // Create new graphic items for bars
    for (int s=0; s<mModel.countSets(); s++) {
        QBarSet *set = mModel.nextSet(0==s);
        for (int c=0; c<mModel.countCategories(); c++) {
            Bar *bar = new Bar(this);
            childItems().append(bar);
            connect(bar,SIGNAL(clicked()),set,SLOT(barClicked()));
        }
    }

    int count = mModel.countCategories();
    for (int i=0; i<count; i++) {
        BarLabel* label = new BarLabel(this);
        label->set(mModel.label(i));
        childItems().append(label);
    }

    count = mModel.countCategories() - 1;   // There is one less separator than columns
    for (int i=0; i<count; i++) {
        Separator* sep = new Separator(this);
        sep->setColor(QColor(255,0,0,255));     // TODO: color for separations from theme
        childItems().append(sep);
    }

    // TODO: if (autolayout) { layoutChanged() } or something
    mLayoutDirty = true;
}

//handlers

void BarPresenterBase::handleModelChanged(int index)
{
//    qDebug() << "BarGroupBase::handleModelChanged" << index;
    dataChanged();
}

void BarPresenterBase::handleDomainChanged(const Domain& domain)
{
//    qDebug() << "BarGroupBase::handleDomainChanged";
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

#include "moc_barpresenterbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
