#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSplineSeries : public QChartSeries
{
    Q_OBJECT
    public:
    explicit QSplineSeries(QObject *parent = 0);
    
    public: // from QChartSeries
    QChartSeriesType type() const { return QChartSeries::SeriesTypeSpline; }
    signals:
    
    public slots:
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSPLINESERIES_H
