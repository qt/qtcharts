#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QScatterSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QScatterSeries : public QChartSeries
{
    Q_OBJECT
public:
    //QScatterSeries(QSeriesData *data, QObject *chart);
    QScatterSeries(QList<qreal> x, QList<qreal> y, QObject *chart = 0);
    ~QScatterSeries();

public: // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeScatter; }

private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    friend class QChart;
    QScatterSeriesPrivate *const d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
