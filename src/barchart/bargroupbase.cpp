#include "bargroupbase.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include "barchartseriesbase.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarGroupBase::BarGroupBase(BarChartSeriesBase& series, QGraphicsItem *parent)
    : ChartItem(parent)
    ,mSeries(series)
    ,mBarDefaultWidth(20) // TODO: remove hard coding, when we have layout code ready
    ,mLayoutSet(false)
    ,mLayoutDirty(true)
    ,mTheme(0)
    ,mSeparatorsVisible(true)
{
    dataChanged();
}

void BarGroupBase::setSeparatorsVisible(bool visible)
{
    mSeparatorsVisible = visible;
}

void BarGroupBase::setSize(const QSizeF& size)
{
    mWidth = size.width();
    mHeight = size.height();
    layoutChanged();
    mLayoutSet = true;
}

void BarGroupBase::setPlotDomain(const PlotDomain& data)
{
    qDebug() << "BarGroupBase::setPlotDomain";
    // TODO:
}

void BarGroupBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!mLayoutSet) {
        qDebug() << "BarGroupBase::paint called without layout set. Aborting.";
        return;
    }
    if (mLayoutDirty) {
        // Layout or data has changed. Need to redraw.
        foreach(QGraphicsItem* i, childItems()) {
            i->paint(painter,option,widget);
        }
    }
}

QRectF BarGroupBase::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}

void BarGroupBase::themeChanged(ChartTheme *theme)
{
    mTheme = theme;
}

void BarGroupBase::setBarWidth( int w )
{
    mBarDefaultWidth = w;
}

int BarGroupBase::addColor( QColor color )
{
    int colorIndex = mColors.count();
    mColors.append(color);
    return colorIndex;
}

void BarGroupBase::resetColors()
{
    mColors.clear();
}

void BarGroupBase::dataChanged()
{
    qDebug() << "BarGroupBase::dataChanged";

    // Find out maximum and minimum of all series
    mMax = mSeries.max();
    mMin = mSeries.min();

    // Delete old bars
    foreach (QGraphicsItem* item, childItems()) {
        delete item;
    }

    // Create new graphic items for bars
    int totalItems = mSeries.countTotalItems();
    for (int i=0; i<totalItems; i++) {
        Bar *bar = new Bar(this);
        childItems().append(bar);
    }

    // TODO: labels from series. This creates just some example labels
    int count = mSeries.countColumns();
    for (int i=0; i<count; i++) {
        BarLabel* label = new BarLabel(this);
        QString text("Label " + QString::number(i));
        label->set(text);
        childItems().append(label);
    }

    count = mSeries.countColumns() - 1; // There is one less separator than columns
    for (int i=0; i<count; i++) {
        Separator* sep = new Separator(this);
        sep->setColor(QColor(255,0,0,255));     // TODO: color for separations from theme
        childItems().append(sep);
    }

    // TODO: if (autolayout) { layoutChanged() } or something
    mLayoutDirty = true;
}

QTCOMMERCIALCHART_END_NAMESPACE
