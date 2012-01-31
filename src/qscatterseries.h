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
    bool setData(QList<qreal> x, QList<qreal> y);

public Q_SLOTS:
    // TODO: also affects opacity of the marker...? To be documented
    void setMarkerColor(QColor color);
    QColor markerColor();
    // TODO: marker shapes: "x", star, rectangle, tilted rect, triangle, circle, dot
    //void setMarkerShape(QChartSeries::MarkerShape/QScatterSeries::MarkerShape shape);

private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    friend class QChart;
    QScatterSeriesPrivate *const d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
