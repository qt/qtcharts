#ifndef PIESLICE_H
#define PIESLICE_H

#include "qchartglobal.h"
#include "charttheme_p.h"
#include "qpieseries.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QColor>
#include <QPen>

#define PIESLICE_LABEL_GAP 5

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieChartItem;
class PieSliceLabel;
class QPieSlice;

class PieSliceData
{
public:
    QPointF m_center;
    qreal m_radius;
    qreal m_startAngle;
    qreal m_angleSpan;

    QPen m_pen;
    QBrush m_brush;

    bool m_isExploded;
    qreal m_explodeDistanceFactor;

    bool m_labelVisible;
    QString m_labelText;
    QFont m_labelFont;
    qreal m_labelArmLengthFactor;
    QPen m_labelArmPen;
};

class PieSlice : public QGraphicsObject
{
    Q_OBJECT

public:
    PieSlice(QGraphicsItem* parent = 0);
    ~PieSlice();

public: // from QGraphicsItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked();
    void hoverEnter();
    void hoverLeave();

public:
    void setSliceData(PieSliceData sliceData);
    void updateGeometry();
    static QPointF sliceCenter(QPointF point, qreal radius, QPieSlice *slice);
    static QPainterPath slicePath(QPointF center, qreal radius, qreal startAngle, qreal angleSpan, qreal* centerAngle, QPointF* armStart);
    static QPainterPath labelArmPath(QPointF start, qreal angle, qreal length, qreal textWidth, QPointF* textStart);
    static QRectF labelTextRect(QFont font, QString text);

private:
    PieSliceData m_data;
    QRectF m_boundingRect;
    QPainterPath m_slicePath;
    QPainterPath m_labelArmPath;
    QRectF m_labelTextRect;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICE_H
