#ifndef PIESLICE_H
#define PIESLICE_H

#include "qchartglobal.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QColor>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieSlice : public QGraphicsItem
{
public:
    PieSlice(const QColor& color, qreal startAngle, qreal span);
    ~PieSlice();

public: // from QGraphicsItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

private:
    QColor m_color;
    qreal m_startAngle;
    qreal m_span;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICE_H
