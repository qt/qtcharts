#ifndef LEGENDSCROLLBUTTON_P_H
#define LEGENDSCROLLBUTTON_P_H

#include <QObject>
#include <qchartglobal.h>
#include <QGraphicsPolygonItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLegend;

class LegendScrollButton : public QGraphicsPolygonItem
{
public:
    enum ScrollButtonId {
        ScrollButtonIdLeft,
        ScrollButtonIdRight,
        ScrollButtonIdUp,
        ScrollButtonIdDown
    };

    explicit LegendScrollButton(ScrollButtonId id, QLegend *legend);
    ScrollButtonId id();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    ScrollButtonId m_id;
    QLegend *m_ledgend;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // LEGENDSCROLLBUTTON_P_H
