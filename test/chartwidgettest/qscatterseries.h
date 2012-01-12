#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include <QGraphicsItem>

class QScatterSeries : public QGraphicsItem
{
public:
    explicit QScatterSeries(QGraphicsItem *parent = 0);

signals:

public slots:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // QSCATTERSERIES_H
