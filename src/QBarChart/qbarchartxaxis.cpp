#include "qbarchartxaxis.h"

QBarChartXAxis::QBarChartXAxis(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}


void QBarChartXAxis::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF QBarChartXAxis::boundingRect() const
{
    QRectF r(scenePos().x(), scenePos().y(), scenePos().x() + mWidth, scenePos().y() + mHeight );
    return r;
}
