#ifndef PIESLICE_H
#define PIESLICE_H

#include "qchartglobal.h"
#include "charttheme_p.h"
#include "qpieseries.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QColor>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PiePresenter;

class PieSlice : public QGraphicsItem
{
public:
    PieSlice(PiePresenter *piePresenter, int seriesIndex, qreal startAngle, qreal span);
    ~PieSlice();

public: // from QGraphicsItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    void updateGeometry();

private:
    QPieSlice sliceData();

private:
    QGraphicsTextItem* m_label;
    int m_seriesIndex;
    qreal m_startAngle;
    qreal m_span;
    QPainterPath m_path;
    QRectF m_rect;
    QPointF m_center;
    QPen m_pen;
    QBrush m_brush;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICE_H
