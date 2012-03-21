#ifndef PIESLICEITEM_H
#define PIESLICEITEM_H

#include "qchartglobal.h"
#include "charttheme_p.h"
#include "qpieseries.h"
#include "qpiesliceprivate_p.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QColor>
#include <QPen>

#define PIESLICE_LABEL_GAP 5

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieChartItem;
class PieSliceLabel;
class QPieSlice;

class PieSliceItem : public QGraphicsObject
{
    Q_OBJECT

public:
    PieSliceItem(QGraphicsItem* parent = 0);
    ~PieSliceItem();

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

#endif // PIESLICEITEM_H
