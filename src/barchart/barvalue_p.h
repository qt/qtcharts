#ifndef BARVALUE_P_H
#define BARVALUE_P_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSet;

// Visual class for floating bar values
// By default these are not visible.
class BarValue : public QGraphicsObject
{
    Q_OBJECT
public:
    BarValue(QBarSet &set, QGraphicsItem *parent = 0);

    void setValueString(QString str);
    QString valueString();

    void setPen(const QPen& pen);
    const QPen& pen();

    void resize(qreal w, qreal h);
    void setPos(qreal x, qreal y);

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public Q_SLOTS:
    void toggleVisible();

private:

    QBarSet& mBarSet;
    QPen mPen;
    QString mValueString;

    qreal mXpos;
    qreal mYpos;
    qreal mWidth;
    qreal mHeight;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARVALUE_P_H
