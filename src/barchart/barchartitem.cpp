#include "barchartitem_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include "qbarseries.h"
#include "qchart.h"
#include "qchartaxis.h"
#include "qchartaxiscategories.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QDebug>
#include <QToolTip>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartItem::BarChartItem(QBarSeries *series, QChart *parent) :
    ChartItem(parent),
    mHeight(0),
    mWidth(0),
    mLayoutSet(false),
    mSeries(series),
    mChart(parent)
{
    connect(series,SIGNAL(showToolTip(QPoint,QString)),this,SLOT(showToolTip(QPoint,QString)));
    connect(series, SIGNAL(updatedBars()), this, SLOT(layoutChanged()));
//TODO:  connect(series,SIGNAL("position or size has changed"), this, SLOT(handleLayoutChanged()));
    connect(series, SIGNAL(restructuredBar(int)), this, SLOT(handleModelChanged(int)));
    setZValue(ChartPresenter::BarSeriesZValue);
    initAxisLabels();
    dataChanged();
}

BarChartItem::~BarChartItem()
{
    disconnect(this,SLOT(showToolTip(QPoint,QString)));
}

void BarChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!mLayoutSet) {
        qDebug() << "BarChartItem::paint called without layout set. Aborting.";
        return;
    }
    foreach(QGraphicsItem* i, childItems()) {
        i->paint(painter,option,widget);
    }
}

QRectF BarChartItem::boundingRect() const
{
    return QRectF(0, 0, mWidth, mHeight);
}

void BarChartItem::dataChanged()
{
    // TODO: performance optimizations. Do we really need to delete and create items every time data is changed or can we reuse them?
    // Delete old bars
    foreach (QGraphicsItem* item, childItems()) {
        delete item;
    }

    mBars.clear();
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

void BarChartItem::layoutChanged()
{
    // Scale bars to new layout
    // Layout for bars:
    if (mSeries->barsetCount() <= 0) {
        qDebug() << "No sets in model!";
        return;
    }

    if (childItems().count() == 0) {
        qDebug() << "WARNING: BarChartitem::layoutChanged called before graphics items are created!";
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
            bar->setPen(mSeries->barsetAt(set)->pen());
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
    update();
}

BarLayout BarChartItem::calculateLayout()
{
    BarLayout layout;
    foreach(Bar* bar, mBars) {
        layout.insert(bar,bar->boundingRect().size());
    }

    return layout;
}

void BarChartItem::applyLayout(const BarLayout &layout)
{
    if (m_animator)
        m_animator->updateLayout(this, layout);
    else
        setLayout(layout);
}

void BarChartItem::setLayout(const BarLayout &layout)
{
    foreach (Bar *bar, layout.keys()) {
        bar->setSize(layout.value(bar));
    }
    update();
}

void BarChartItem::initAxisLabels()
{
    int count = mSeries->categoryCount();
    if (0 == count) {
        return;
    }

    mChart->axisX()->setTicksCount(count+2);

    qreal min = 0;
    qreal max = count+1;

    mChart->axisX()->setMin(min);
    mChart->axisX()->setMax(max);

    QChartAxisCategories* categories = mChart->axisX()->categories();
    categories->clear();
    for (int i=0; i<count; i++) {
        categories->insert(i+1,mSeries->categoryName(i));
    }



    mChart->axisX()->setLabelsVisible(true);
}

//handlers

void BarChartItem::handleModelChanged(int index)
{
    Q_UNUSED(index)
    dataChanged();
}

void BarChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    // TODO:
    Q_UNUSED(minX)
    Q_UNUSED(maxX)
    Q_UNUSED(minY)
    Q_UNUSED(maxY)

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

void BarChartItem::handleGeometryChanged(const QRectF& rect)
{
    mWidth = rect.width();
    mHeight = rect.height();
    layoutChanged();
    mLayoutSet = true;
    setPos(rect.topLeft());
}

void BarChartItem::handleLayoutChanged()
{
    BarLayout layout = calculateLayout();
    applyLayout(layout);
    update();
}


void BarChartItem::showToolTip(QPoint pos, QString tip)
{
    // TODO: cool tooltip instead of default
    QToolTip::showText(pos,tip);
}

#include "moc_barchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
