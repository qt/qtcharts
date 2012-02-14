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
class PieSliceLabel;

class PieSlice : public QGraphicsObject
{
    Q_OBJECT

public:
    PieSlice(QPieSliceId id, QPieSeries *series, QGraphicsItem* parent = 0);
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

public:
    void updateGeometry(QRectF rect, qreal startAngle, qreal span);
    void updateData();

private:
    QPieSliceId m_id;
    QPieSeries* m_series;
    QPieSlice m_data;
    PieSliceLabel* m_slicelabel;
    QPainterPath m_path;
    QRectF m_rect;
    bool m_isHovering;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICE_H
