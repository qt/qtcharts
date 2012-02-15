#ifndef PIELABEL_H
#define PIELABEL_H

#include "qchartglobal.h"
#include <QGraphicsItem>
#include <QPen>
#include <QFontMetricsF>

class QGraphicsTextItem;
QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieSliceLabel : public QGraphicsItem
{
public:
    PieSliceLabel(QGraphicsItem* parent = 0);
    ~PieSliceLabel() {};

public: // from QGraphicsItem
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    void updateGeometry();

    void setArmStartPoint(QPointF point) { m_armStartPoint = point; }
    QPointF armStartPoint() const { return m_armStartPoint; }

    void setArmAngle(qreal angle) { m_armAngle = angle; }
    qreal armAngle() const { return m_armAngle; }

    void setArmLength(qreal len) { m_armLength = len; }
    qreal armLength() const { return m_armLength; }

    void setText(QString text) { m_text = text; }
    QString text() const { return m_text; }

    void setPen(QPen pen) { m_pen = pen; }
    QPen pen() const { return m_pen; }

    void setFont(QFont font) { m_font = font; }
    QFont font() const { return m_font; }

private:
    QPointF m_armStartPoint;
    qreal m_armAngle;
    qreal m_armLength;
    QString m_text;
    QRectF m_rect;
    QPainterPath m_armPath;
    QRectF m_textRect;
    QPen m_pen;
    QFont m_font;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIELABEL_H
