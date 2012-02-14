#ifndef PIELABEL_H
#define PIELABEL_H

#include "qchartglobal.h"
#include <QGraphicsItem>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieSliceLabel : public QGraphicsItem
{
public:
    PieSliceLabel(QGraphicsItem* parent = 0);
    ~PieSliceLabel();

public: // from QGraphicsItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    void updateGeometry(const QPointF& startPoint, qreal armAngle, qreal armLength);
    void setLabel(QString label);
    QString label() const {return m_label;}
    void setPen(QPen pen);

private:
    QString m_label;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_pen;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIELABEL_H
