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
#include "chartdataset_p.h"
#include <QDebug>
#include <QToolTip>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartItem::BarChartItem(QBarSeries *series, ChartPresenter *presenter) :
    ChartItem(presenter),
    mLayoutSet(false),
    mSeries(series)
{
    connect(series, SIGNAL(showToolTip(QPoint,QString)), this, SLOT(showToolTip(QPoint,QString)));
    connect(series, SIGNAL(updatedBars()), this, SLOT(handleLayoutChanged()));
//TODO:  connect(series,SIGNAL("position or size has changed"), this, SLOT(handleLayoutChanged()));
    connect(series, SIGNAL(restructuredBar(int)), this, SLOT(handleModelChanged(int)));
    setZValue(ChartPresenter::BarSeriesZValue);
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

    foreach(QGraphicsItem* i, childItems())
        i->paint(painter,option,widget);
}

QRectF BarChartItem::boundingRect() const
{
    return m_rect;
}

void BarChartItem::dataChanged()
{
    // TODO: performance optimizations. Do we really need to delete and create items every time data is changed or can we reuse them?
    // Delete old bars
    foreach (QGraphicsItem *item, childItems())
        delete item;

    mBars.clear();
    mFloatingValues.clear();
    mLayout.clear();

    // Create new graphic items for bars
    for (int c = 0; c < mSeries->categoryCount(); c++) {
        QString category = mSeries->categoryName(c);
        for (int s = 0; s < mSeries->barsetCount(); s++) {
            QBarSet *set = mSeries->barsetAt(s);
            Bar *bar = new Bar(category,this);
            childItems().append(bar);
            mBars.append(bar);
            connect(bar, SIGNAL(clicked(QString)), set, SIGNAL(clicked(QString)));
            connect(bar, SIGNAL(rightClicked(QString)), set, SIGNAL(rightClicked(QString)));
            connect(bar, SIGNAL(hoverEntered(QPoint)), set, SLOT(barHoverEnterEvent(QPoint)));
            connect(bar, SIGNAL(hoverLeaved()), set, SLOT(barHoverLeaveEvent()));
            mLayout.append(QRectF(0, 0, 0, 0));
        }
    }

    // Create floating values
    for (int category = 0; category < mSeries->categoryCount(); category++) {
        for (int s = 0; s < mSeries->barsetCount(); s++) {
            QBarSet *set = mSeries->barsetAt(s);
            BarValue *value = new BarValue(*set, this);
            childItems().append(value);
            mFloatingValues.append(value);
            connect(set, SIGNAL(toggleFloatingValues()), value, SLOT(toggleVisible()));
        }
    }
}
QVector<QRectF> BarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accurancy (we might get some compiler warnings... :)
    qreal categoryCount = mSeries->categoryCount();
    qreal setCount = mSeries->barsetCount();

    qreal width = geometry().width();
    qreal height = geometry().height();

    qreal max = mSeries->max();

    // Domain:
    if (mDomainMaxY > max) {
        max = mDomainMaxY;
    }

    qreal scale = (height / max);
    qreal categoryWidth = width / categoryCount;
    qreal barWidth = categoryWidth / (setCount+1);

    int itemIndex(0);
    for (int category = 0; category < categoryCount; category++) {
        qreal xPos = categoryWidth * category + barWidth / 2;
        qreal yPos = height;
        for (int set = 0; set < setCount; set++) {
            qreal barHeight = mSeries->valueAt(set, category) * scale;
            Bar* bar = mBars.at(itemIndex);

            QRectF rect(xPos, yPos - barHeight, barWidth, barHeight);
            layout.append(rect);
            bar->setPen(mSeries->barsetAt(set)->pen());
            bar->setBrush(mSeries->barsetAt(set)->brush());
            itemIndex++;
            xPos += barWidth;
        }
    }

    // Position floating values
    itemIndex = 0;
    for (int category = 0; category < mSeries->categoryCount(); category++) {
        qreal xPos = categoryWidth * category  + barWidth;
        qreal yPos = height;
        for (int set=0; set < mSeries->barsetCount(); set++) {
            qreal barHeight = mSeries->valueAt(set, category) * scale;
            BarValue* value = mFloatingValues.at(itemIndex);

            QBarSet* barSet = mSeries->barsetAt(set);
            value->resize(100, 50);  // TODO: proper layout for this.
            value->setPos(xPos, yPos-barHeight / 2);
            value->setPen(barSet->floatingValuePen());

            if (mSeries->valueAt(set,category) != 0) {
                value->setValueString(QString::number(mSeries->valueAt(set, category)));
            } else {
                value->setValueString(QString(""));
            }

            itemIndex++;
            xPos += barWidth;
        }
    }

    return layout;
}

void BarChartItem::applyLayout(const QVector<QRectF> &layout)
{
    if (animator())
        animator()->updateLayout(this, mLayout, layout);
    else
        setLayout(layout);
}

void BarChartItem::setLayout(const QVector<QRectF> &layout)
{
    mLayout = layout;

    for (int i=0; i < mBars.count(); i++)
        mBars.at(i)->setRect(layout.at(i));

    update();
}

//handlers

void BarChartItem::handleModelChanged(int index)
{
    Q_UNUSED(index)
    dataChanged();
}

void BarChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    mDomainMinX = minX;
    mDomainMaxX = maxX;
    mDomainMinY = minY;
    mDomainMaxY = maxY;
    handleLayoutChanged();
}

void BarChartItem::handleGeometryChanged(const QRectF &rect)
{
    m_rect = rect;
    handleLayoutChanged();
    mLayoutSet = true;
    setPos(rect.topLeft());
}

void BarChartItem::handleLayoutChanged()
{
    QVector<QRectF> layout = calculateLayout();
    applyLayout(layout);
    update();
}


void BarChartItem::showToolTip(QPoint pos, QString tip)
{
    // TODO: cool tooltip instead of default
    QToolTip::showText(pos, tip);
}

#include "moc_barchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
