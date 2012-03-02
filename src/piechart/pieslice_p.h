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
class PiePresenter;
class PieSliceLabel;
class QPieSlice;

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

public Q_SLOTS:
    void setPieRect(QRectF rect);
    void updateGeometry();
    void updateData(const QPieSlice *sliceData);

public:
    static QPainterPath slicePath(QPointF center, qreal radius, qreal startAngle, qreal angleSpan, bool exploded, qreal explodeDistance, qreal* centerAngle, QPointF* armStart);
    static QPainterPath labelArmPath(QPointF start, qreal angle, qreal length, qreal textWidth, QPointF* textStart);
    static QRectF labelTextRect(QFont font, QString text);

private:
    QRectF m_pieRect;

    QPainterPath m_slicePath;
    qreal m_startAngle;
    qreal m_angleSpan;
    bool m_isExploded;
    qreal m_explodeDistance;
    bool m_labelVisible;
    QPen m_pen;
    QBrush m_brush;

    QPainterPath m_labelArmPath;
    qreal m_labelArmLength;
    QPen m_labelArmPen;

    QRectF m_labelTextRect;
    QFont m_labelFont;
    QString m_labelText;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICE_H
