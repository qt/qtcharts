#ifndef AXIS_H_
#define AXIS_H_

#include <qchartglobal.h>
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Axis: public QGraphicsItem
{
public:
    Axis(QGraphicsItem* parent = 0);
    virtual ~Axis();

    //from QGraphicsItem
    virtual QPainterPath shape() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setLength(int length);
    void setWidth(int width);

private:
    QPainterPath m_path;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* AXIS_H_ */
