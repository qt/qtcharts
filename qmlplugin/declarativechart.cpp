#include "declarativechart.h"
#include <QPainter>

#ifndef QTQUICK2
DeclarativeChart::DeclarativeChart(QDeclarativeItem *parent)
    : QDeclarativeItem(parent)
{
    // need to disable this flag to draw inside a QDeclarativeItem
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}
#else
DeclarativeChart::DeclarativeChart(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{

}
#endif

#ifndef QTQUICK2
void DeclarativeChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
#else
void DeclarativeChart::paint(QPainter *painter)
#endif
{
    drawChart(painter, boundingRect());
}

