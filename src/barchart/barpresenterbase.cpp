#include "barpresenterbase_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include "qbarset.h"
#include "qbarseries.h"
#include "qchart.h"
#include "qchartaxis.h"
#include "qchartaxiscategories.h"
#include <QDebug>
#include <QToolTip>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarPresenterBase::BarPresenterBase(QBarSeries *series, QChart *parent)
    : ChartItem(parent)
    ,mLayoutSet(false)
    ,mSeparatorsEnabled(false)
    ,mSeries(series)
    ,mChart(parent)
{
    connect(series,SIGNAL(showToolTip(QPoint,QString)),this,SLOT(showToolTip(QPoint,QString)));
    initAxisLabels();
    dataChanged();
}

BarPresenterBase::~BarPresenterBase()
{
    disconnect(this,SLOT(showToolTip(QPoint,QString)));
}

void BarPresenterBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!mLayoutSet) {
        qDebug() << "BarPresenterBase::paint called without layout set. Aborting.";
        return;
    }
    foreach(QGraphicsItem* i, childItems()) {
        i->paint(painter,option,widget);
    }
}

QRectF BarPresenterBase::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}

void BarPresenterBase::dataChanged()
{
    // TODO: performance optimizations. Do we really need to delete and create items every time data is changed or can we reuse them?
    // Delete old bars
    foreach (QGraphicsItem* item, childItems()) {
        delete item;
    }

    mBars.clear();
    mSeparators.clear();
    mFloatingValues.clear();

    // Create new graphic items for bars
    for (int c=0; c<mSeries->categoryCount(); c++) {
        QString category = mSeries->categoryName(c);
        for (int s=0; s<mSeries->barsetCount(); s++) {
            QBarSet *set = mSeries->barsetAt(s);
            Bar *bar = new Bar(category,this);
            childItems().append(bar);
            mBars.append(bar);
            connect(bar,SIGNAL(clicked(QString)),set,SIGNAL(clicked(QString)));
            connect(bar,SIGNAL(rightClicked(QString)),set,SIGNAL(rightClicked(QString)));
            connect(bar,SIGNAL(hoverEntered(QPoint)),set,SLOT(barHoverEnterEvent(QPoint)));
            connect(bar,SIGNAL(hoverLeaved()),set,SLOT(barHoverLeaveEvent()));
        }
    }

    // Create separators
    int count = mSeries->categoryCount() - 1;   // There is one less separator than columns
    for (int i=0; i<count; i++) {
        Separator* sep = new Separator(this);
        sep->setColor(QColor(255,0,0,255));     // TODO: color for separations from theme
        sep->setVisible(mSeparatorsEnabled);
        childItems().append(sep);
        mSeparators.append(sep);
    }

    // Create floating values
    for (int category=0; category<mSeries->categoryCount(); category++) {
        for (int s=0; s<mSeries->barsetCount(); s++) {
            QBarSet *set = mSeries->barsetAt(s);
            BarValue *value = new BarValue(*set, this);
            childItems().append(value);
            mFloatingValues.append(value);
            connect(set,SIGNAL(toggleFloatingValues()),value,SLOT(toggleVisible()));
        }
    }
}

void BarPresenterBase::initAxisLabels()
{
    int count = mSeries->categoryCount();
    if (0 == count) {
        return;
    }

    mChart->axisX()->setTicksCount(count);

    qreal min = 0;
    qreal max = mSeries->categoryCount();

    mChart->axisX()->setMin(min);
    mChart->axisX()->setMax(max);
    qreal step = (max-min)/count;
    QChartAxisCategories& categories = mChart->axisX()->categories();
    categories.clear();
    for (int i=0; i<count; i++) {
        qDebug() << "initAxisLabels" << min << mSeries->categoryName(i);
        categories.insert(min,mSeries->categoryName(i));
        min += step;
    }
    mChart->axisX()->setLabelsVisible(true);
}

//handlers

void BarPresenterBase::handleModelChanged(int index)
{
//    qDebug() << "BarPresenterBase::handleModelChanged" << index;
    dataChanged();
}

void BarPresenterBase::handleDomainChanged(const Domain& domain)
{
    qDebug() << "BarPresenterBase::handleDomainChanged";
    /*
    int count = mSeries->categoryCount();
    if (0 == count) {
        return;
    }

    // Position labels to domain
    qreal min = domain.minX();
    qreal max = domain.maxX();
    qreal step = (max-min)/count;
    QChartAxisCategories& categories = mChart->axisX()->categories();
    categories.clear();
    for (int i=0; i<count; i++) {
        categories.insert(min,mSeries->categoryName(i));
        min += step;
    }
    */
}

void BarPresenterBase::handleGeometryChanged(const QRectF& rect)
{
    mWidth = rect.width();
    mHeight = rect.height();
    layoutChanged();
    mLayoutSet = true;
    setPos(rect.topLeft());
}

void BarPresenterBase::showToolTip(QPoint pos, QString tip)
{
    // TODO: cool tooltip instead of default
    QToolTip::showText(pos,tip);
}

void BarPresenterBase::enableSeparators(bool enabled)
{
    for (int i=0; i<mSeparators.count(); i++) {
        mSeparators.at(i)->setVisible(enabled);
    }
    mSeparatorsEnabled = enabled;
}

#include "moc_barpresenterbase_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
