#include "bargroupbase.h"
#include "bar_p.h"
#include "barlabel_p.h"
#include "separator_p.h"
#include "barchartseriesbase.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarGroupBase::BarGroupBase(BarChartSeriesBase& series, QGraphicsItem *parent)
    : ChartItem(parent)
    ,mBarDefaultWidth(20) // TODO: remove hard coding, when we have layout code ready
    ,mLayoutSet(false)
    ,mLayoutDirty(true)
    ,mTheme(0)
    ,mSeparatorsVisible(true)
    ,mModel(series.model())
{
}

void BarGroupBase::setSeparatorsVisible(bool visible)
{
    mSeparatorsVisible = visible;
}

void BarGroupBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "BarGroupBase::paint" << childItems().count();
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

QRectF BarGroupBase::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}
/*
void BarGroupBase::themeChanged(ChartTheme *theme)
{
    qDebug() << "BarGroupBase::themeChanged"
//    mTheme = theme;
}
*/
void BarGroupBase::setBarWidth( int w )
{
    mBarDefaultWidth = w;
}

int BarGroupBase::addColor( QColor color )
{
    qDebug() << "BarGroupBase::addColor";
    int colorIndex = mColors.count();
    mColors.append(color);
    return colorIndex;
}

void BarGroupBase::resetColors()
{
    qDebug() << "BarGroupBase::resetColors";
    mColors.clear();
}

void BarGroupBase::dataChanged()
{
    qDebug() << "BarGroupBase::dataChanged";

    // Delete old bars
    foreach (QGraphicsItem* item, childItems()) {
        delete item;
    }

    // Create new graphic items for bars
    int totalItems = mModel.countTotalItems();  // mSeries.countTotalItems();
    for (int i=0; i<totalItems; i++) {
        Bar *bar = new Bar(this);
        childItems().append(bar);
    }

    // TODO: labels from series. This creates just some example labels
    int count = mModel.countColumns();    // mSeries.countColumns();
    for (int i=0; i<count; i++) {
        BarLabel* label = new BarLabel(this);
        QString text("Label " + QString::number(i));
        label->set(text);
        childItems().append(label);
    }

    count = mModel.countColumns() - 1;    // mSeries.countColumns() - 1; // There is one less separator than columns
    for (int i=0; i<count; i++) {
        Separator* sep = new Separator(this);
        sep->setColor(QColor(255,0,0,255));     // TODO: color for separations from theme
        childItems().append(sep);
    }

    // TODO: if (autolayout) { layoutChanged() } or something
    mLayoutDirty = true;
}

//handlers

void BarGroupBase::handleModelChanged(int index)
{
    qDebug() << "BarGroupBase::handleModelChanged" << index;
    dataChanged();
}

void BarGroupBase::handleDomainChanged(const Domain& domain)
{
    qDebug() << "BarGroupBase::handleDomainChanged";
    dataChanged();
}

void BarGroupBase::handleGeometryChanged(const QRectF& rect)
{
    qDebug() << "BarGroupBase::handleGeometryChanged";
    mWidth = rect.width();
    mHeight = rect.height();
    layoutChanged();
    mLayoutSet = true;
    setPos(rect.topLeft());
}

#include "moc_bargroupbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
