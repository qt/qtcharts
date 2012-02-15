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
    enum MarkerShape {
        // TODO: to be defined by the graphics design
        // TODO: marker shapes: "x", star, rectangle, tilted rect, triangle, circle, dot
        MarkerShapeDefault = 0,
        MarkerShapePoint,
        MarkerShapeX,
        MarkerShapeRectangle,
        MarkerShapeTiltedRectangle,
        MarkerShapeTriangle,
        MarkerShapeCircle
    };

public:
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
    //TODO: insertData?

    void setMarkerPen(QPen pen);
    QPen markerPen();
    void setMarkerBrush(QBrush brush);
    QBrush markerBrush();
    void setMarkerShape(MarkerShape shape);
    MarkerShape markerShape();
    // TODO: marker size?

Q_SIGNALS:
    // TODO: move to PIMPL for simplicity or does the user ever need these signals?
    // TODO: more finegrained signaling for performance reasons
    // (check QPieSeries implementation with change sets)
    void changed();

//public Q_SLOTS:
private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    QScatterSeriesPrivate *const d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
