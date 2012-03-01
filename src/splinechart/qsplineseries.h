#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include "qchartglobal.h"
#include <QtGlobal>
#include "qchartseries.h"
#include <QList>
#include <QPointF>

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
    QList<qreal> getFirstControlPoints(QList<qreal> rhs);

    int count() const { return m_data.size(); }

    QPointF at(int index) const { return m_data[index]; }
    QPointF controlPoint(int index) const { return m_controlPoints[index]; }

    signals:
    
    public slots:

    private:
    QList<QPointF> m_data;
    QList<QPointF> m_controlPoints;
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSPLINESERIES_H
