#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSplineSeries : public QChartSeries
{
    Q_OBJECT
    public:

    QSplineSeries(QObject *parent = 0);
    QChartSeriesType type() const { return QChartSeries::SeriesTypeSpline; }
    void addData(QPointF value);
    QSplineSeries& operator << (const QPointF &value);
    void calculateControlPoints();

    signals:
    
    public slots:

    private:
    QList<QPointF> m_data;
    QList<QPointF> m_controlPoints;
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSPLINESERIES_H
