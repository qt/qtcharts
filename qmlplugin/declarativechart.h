#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtCore/QtGlobal>
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    #include <QDeclarativeItem>
#else
    #include <QtQuick/QQuickPaintedItem>
#endif
#include <QColor>
#include "../src/chart.h"

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
class DeclarativeChart : public QDeclarativeItem, public Chart
#else
class DeclarativeChart : public QQuickPaintedItem, public Chart
#endif
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    DeclarativeChart(QDeclarativeItem *parent = 0);
#else
    DeclarativeChart(QQuickItem *parent = 0);
#endif

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
#else
    void paint(QPainter *painter);
#endif
};


#endif // DECLARATIVECHART_H
