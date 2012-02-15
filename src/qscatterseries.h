#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include "qchartseries.h"
#include <QRectF>
#include <QColor>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QScatterSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QScatterSeries : public QChartSeries
{
    Q_OBJECT
public:
    //QScatterSeries(QSeriesData *data, QObject *chart);
    QScatterSeries(QObject *parent = 0);
    ~QScatterSeries();

public: // from QChartSeries
    QChartSeriesType type() const { return QChartSeries::SeriesTypeScatter; }

public:
    // TODO: the name of the function? addPoint? addData? addValue?
    void addData(QPointF value);
    QScatterSeries& operator << (const QPointF &value);

    void setData(QList<QPointF> data);

    QList<QPointF> data();

    //TODO? void insertData(int index, QPointF data);

    void setMarkerPen(QPen pen);
    QPen markerPen();
    // TODO: marker shapes: "x", star, rectangle, tilted rect, triangle, circle, dot
    //void setMarkerShape(MarkerShape shape);

Q_SIGNALS:
    // TODO: move to PIMPL?
    // TODO: more finegrained signaling for performance reasons
    void changed();

//public Q_SLOTS:
private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    QScatterSeriesPrivate *const d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
