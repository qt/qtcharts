#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include "qchartglobal.h"
#include <QtGlobal>
#include "qlineseries.h"
#include <QList>
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSplineSeries : public QLineSeries
{
    Q_OBJECT
    public:

    QSplineSeries(QObject *parent = 0);
    QSeriesType type() const { return QSeries::SeriesTypeSpline; }

//    int count() const { return m_x.size(); }
    QPointF controlPoint(int index) const { return m_controlPoints[index]; }

    private:
    void calculateControlPoints();
    QList<qreal> getFirstControlPoints(QList<qreal> rhs);

    private slots:
    void updateControlPoints();

    private:
    QList<QPointF> m_controlPoints;
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSPLINESERIES_H
