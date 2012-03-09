#ifndef QLEGEND_H
#define QLEGEND_H

#include "qchartglobal.h"
#include "qseries.h"
#include <QGraphicsObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain;

class QLegend : public QGraphicsObject
{
    Q_OBJECT
public:

    explicit QLegend(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

signals:
    
public slots:
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);

private:

    QRectF mBoundingRect;
    QList<QSeries*> mSeriesList;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
