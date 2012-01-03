#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtCore/QtGlobal>
#ifndef QTQUICK2
    #include <QDeclarativeItem>
#else
    #include <QtQuick/QQuickPaintedItem>
#endif
#include <QColor>
#include "../src/chart.h"

#ifndef QTQUICK2
class DeclarativeChart : public QDeclarativeItem, public Chart
#else
class DeclarativeChart : public QQuickPaintedItem, public Chart
#endif
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
#ifndef QTQUICK2
    DeclarativeChart(QDeclarativeItem *parent = 0);
#else
    DeclarativeChart(QQuickItem *parent = 0);
#endif

#ifndef QTQUICK2
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
#else
    void paint(QPainter *painter);
#endif
};


#endif // DECLARATIVECHART_H
