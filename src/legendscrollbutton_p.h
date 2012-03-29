#ifndef LEGENDSCROLLBUTTON_P_H
#define LEGENDSCROLLBUTTON_P_H

#include <QObject>
#include <qchartglobal.h>
#include <QGraphicsPolygonItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class LegendScrollButton : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    enum ScrollButtonId {
        ScrollButtonIdLeft,
        ScrollButtonIdRight,
        ScrollButtonIdUp,
        ScrollButtonIdDown
    };

    explicit LegendScrollButton(ScrollButtonId id, QGraphicsItem *parent = 0);
    ScrollButtonId id();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked(QGraphicsSceneMouseEvent* event);
    
public Q_SLOTS:

private:

    ScrollButtonId mId;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // LEGENDSCROLLBUTTON_P_H
