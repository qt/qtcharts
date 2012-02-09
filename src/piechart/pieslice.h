#ifndef PIESLICE_H
#define PIESLICE_H

#include "qchartglobal.h"
#include "charttheme_p.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QColor>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PiePresentation;

class PieSlice : public QGraphicsItem
{
public:
    PieSlice(PiePresentation *piePresentation, int seriesIndex, qreal startAngle, qreal span);
    ~PieSlice();

public: // from QGraphicsItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int m_seriesIndex;
    qreal m_startAngle;
    qreal m_span;
    QRectF m_rect;
    //SeriesTheme m_theme;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICE_H
