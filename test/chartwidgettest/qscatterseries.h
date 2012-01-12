#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include <QGraphicsItem>

// TODO:
#define QChartDataPoint QList<QVariant>

class QSeriesPointGraphicsItem;

class QScatterSeries : public QGraphicsItem
{
public:
    QScatterSeries(QGraphicsItem *parent = 0);
    void setData(QList<QChartDataPoint> data);
//    void setData(QList<int> data);

signals:

public slots:

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // QSCATTERSERIES_H
