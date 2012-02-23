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
    void addData(QPointF value);
    void addData(QList<QPointF> points);
    void setData(QList<QPointF> points);
    QScatterSeries& operator << (const QPointF &value);
    QScatterSeries& operator << (QList<QPointF> points);
    QList<QPointF> data();
    //TODO: insertData?

    QPen markerPen();
    QBrush markerBrush();
    MarkerShape markerShape();
    // TODO: marker size?

public Q_SLOTS:
    void setMarkerPen(QPen pen);
    void setMarkerBrush(QBrush brush);
    void setMarkerShape(MarkerShape shape);

Q_SIGNALS:
    void clicked(/* TODO: parameters? */);
    void hoverEnter(/* TODO: parameters? */);
    void hoverLeave(/* TODO: parameters? */);
    // TODO: move to PIMPL for simplicity or does the user ever need changed signals?
    // TODO: more finegrained signaling for performance reasons
    // (check QPieSeries implementation with change sets)
    void changed();

private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    QScatterSeriesPrivate *const d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
