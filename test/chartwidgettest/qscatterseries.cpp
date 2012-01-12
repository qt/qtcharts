#include "qscatterseries.h"
#include "qseriespointgraphicsitem.h"
#include <QPainter>
#include <QGraphicsScene>

QScatterSeries::QScatterSeries(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}

QRectF QScatterSeries::boundingRect() const
{
    return QRectF(0, 50, 100, 100);
}

void QScatterSeries::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawRect(boundingRect());
}

void QScatterSeries::setData(QList<QChartDataPoint> data)
//void QScatterSeries::setData(QList<int> data)
{
    foreach(QChartDataPoint point, data) {
        // TODO: ownership?
        // TODO: position
        QSeriesPointGraphicsItem *item = new QSeriesPointGraphicsItem(
                    point[0].toReal(), 100-point[1].toReal(), this);
    }
}
