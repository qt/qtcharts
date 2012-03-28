#ifndef BAR_H
#define BAR_H

#include "qchartglobal.h"
#include <QGraphicsRectItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Single visual bar item of chart
class Bar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bar(QString category, QGraphicsItem *parent = 0);

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

Q_SIGNALS:
    void clicked(QString category);
    void rightClicked(QString category);
    void hoverEntered(QPoint pos);
    void hoverLeaved();

private:
    QString m_Category;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
