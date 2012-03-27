#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include <qchartglobal.h>
#include <qlineseries.h>
#include <QList>
#include <QPointF>
#include <QtGlobal>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QSplineSeries : public QLineSeries
{
    Q_OBJECT
public:

    QSplineSeries(QObject *parent = 0);
    QSeriesType type() const {return QSeries::SeriesTypeSpline;}

//    int count() const { return m_x.size(); }
    QPointF controlPoint(int index) const {return m_controlPoints[index];}
    bool setModel(QAbstractItemModel *model);

    void setModelMapping(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);
    void setModelMappingShift(int first, int count);

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
