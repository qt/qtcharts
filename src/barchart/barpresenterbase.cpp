#include "barpresenterbase.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include "qbarset.h"
#include "qbarchartseries.h"
#include <QDebug>
#include <QToolTip>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarPresenterBase::BarPresenterBase(QBarChartSeries *series, QGraphicsItem *parent)
    : ChartItem(parent)
    ,mBarDefaultWidth(20) // TODO: remove hard coding, when we have layout code ready
    ,mLayoutSet(false)
    ,mLayoutDirty(true)
    ,mSeries(series)
{
    connect(series,SIGNAL(floatingValuesEnabled(bool)),this,SLOT(enableFloatingValues(bool)));
    connect(series,SIGNAL(toolTipEnabled(bool)),this,SLOT(enableToolTip(bool)));
    connect(series,SIGNAL(separatorsEnabled(bool)),this,SLOT(enableSeparators(bool)));
    connect(series,SIGNAL(showToolTip(QPoint,QString)),this,SLOT(showToolTip(QPoint,QString)));
    dataChanged();
}

BarPresenterBase::~BarPresenterBase()
{
    disconnect(this,SLOT(enableFloatingValues(bool)));
    disconnect(this,SLOT(enableToolTip(bool)));
    disconnect(this,SLOT(enableSeparators(bool)));
    disconnect(this,SLOT(showToolTip(QPoint,QString)));
    delete mSeries;
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
    for (int c=0; c<mSeries->countCategories(); c++) {
        for (int s=0; s<mSeries->countSets(); s++) {
            QBarSet *set = mSeries->setAt(s);
            Bar *bar = new Bar(this);
            childItems().append(bar);
            mBars.append(bar);
            connect(bar,SIGNAL(clicked()),set,SLOT(barClicked()));
            // TODO: should the event be passed to set or not?
            connect(bar,SIGNAL(hoverEntered(QPoint)),set,SLOT(barHoverEntered(QPoint)));
            connect(bar,SIGNAL(hoverLeaved()),set,SLOT(barHoverLeaved()));
        }
    }

    // Create labels
    int count = mSeries->countCategories();
    for (int i=0; i<count; i++) {
        BarLabel* label = new BarLabel(this);
        label->set(mSeries->label(i));
        childItems().append(label);
        mLabels.append(label);
    }

    // Create separators
    count = mSeries->countCategories() - 1;   // There is one less separator than columns
    for (int i=0; i<count; i++) {
        Separator* sep = new Separator(this);
        sep->setColor(QColor(255,0,0,255));     // TODO: color for separations from theme
        childItems().append(sep);
        mSeparators.append(sep);
    }

    // Create floating values
    for (int category=0; category<mSeries->countCategories(); category++) {
        for (int s=0; s<mSeries->countSets(); s++) {
            QBarSet *set = mSeries->setAt(s);
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

void BarPresenterBase::enableFloatingValues(bool enabled)
{
    mFloatingValuesEnabled = enabled;
}

void BarPresenterBase::enableToolTip(bool enabled)
{
    mToolTipEnabled = enabled;
}

void BarPresenterBase::enableSeparators(bool enabled)
{
    mSeparatorsEnabled = enabled;
}

void BarPresenterBase::showToolTip(QPoint pos, QString tip)
{
    if (mToolTipEnabled) {
        // TODO: cool tooltip instead of default
        QToolTip::showText(pos,tip);
    }
}

#include "moc_barpresenterbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
