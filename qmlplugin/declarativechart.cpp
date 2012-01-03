#include "declarativechart.h"
#include <QPainter>

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
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

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
void DeclarativeChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
#else
void DeclarativeChart::paint(QPainter *painter)
#endif
{
    drawChart(painter, boundingRect());
}

