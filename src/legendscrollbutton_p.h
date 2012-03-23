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

signals:
    void clicked(QGraphicsSceneMouseEvent* event);
    
public slots:

private:

    ScrollButtonId mId;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // LEGENDSCROLLBUTTON_P_H
