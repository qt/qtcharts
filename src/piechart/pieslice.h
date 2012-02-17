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
    void handleSliceDataChanged();
    void setPieRect(QRectF rect);
    void updateGeometry();
    void updateData(const QPieSlice *sliceData);

private:
    PieSliceLabel* m_slicelabel;

    QRectF m_pieRect;
    QPainterPath m_path;

    qreal m_angle;
    qreal m_span;
    bool m_isExploded;

    QPen m_pen;
    QBrush m_brush;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICE_H
