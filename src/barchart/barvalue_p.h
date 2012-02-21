#ifndef BARVALUE_P_H
#define BARVALUE_P_H

#include "qchartglobal.h"
#include <QGraphicsItem>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE


// Visual class for floating bar values
// TODO: fonts, colors etc.
// By default these are not visible.
class BarValue : public QGraphicsItem
{
public:
    BarValue(QGraphicsItem *parent = 0);

    void setValueString(QString str);
    QString valueString();

    void setPen(const QPen& pen);
    const QPen& pen();

    void resize(qreal w, qreal h);
    void setPos(qreal x, qreal y);

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    QPen mPen;
    QString mValueString;

    qreal mXpos;
    qreal mYpos;
    qreal mWidth;
    qreal mHeight;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARVALUE_P_H
