#ifndef BARLABEL_H
#define BARLABEL_H

#include "chartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class BarLabel : public ChartItem
{
public:
    BarLabel(QGraphicsItem* parent = 0);

    void set(QString label);
    void setPos(qreal x, qreal y);

    // From ChartItem
    void setSize(const QSize &size);
    void setPlotDomain(const PlotDomain& data);

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    PlotDomain mDomain;
    QSize mSize;
    QString mLabel;
    qreal mXpos;
    qreal mYpos;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARLABEL_H
