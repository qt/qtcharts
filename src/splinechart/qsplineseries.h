#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include "qchartglobal.h"
#include <QtGlobal>
#include "qxyseries.h"
#include <QList>
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QSplineSeries : public QXYSeries
{
    Q_OBJECT
public:

    QSplineSeries(QObject *parent = 0);
    QSeriesType type() const {return QSeries::SeriesTypeSpline;}

//    int count() const { return m_x.size(); }
    QPointF controlPoint(int index) const {return m_controlPoints[index];}

    // TODO: allow the user to set custom control points
//    void setCustomControlPoints(QList<QPointsF> controlPoints);
//    bool calculateControlPointsAutomatically();
//    void setCalculateControlPointsAutomatically();


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
