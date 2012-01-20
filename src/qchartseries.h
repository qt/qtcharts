#ifndef QCHARTSERIES_H
#define QCHARTSERIES_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QChartSeries : public QObject
{

public:
    enum QChartSeriesType {
        SeriesTypeLine = 0,
//        SeriesTypeArea,
//        SeriesTypeBar,
//        SeriesTypePie,
        SeriesTypeScatter
//        SeriesTypeSpline
    };

protected:
    QChartSeries(QObject *parent = 0) : QObject(parent) {};

public:
    virtual ~QChartSeries() {};

    //factory method
    static QChartSeries* create(QObject* parent = 0) { return 0;}
    //pure virtual
    virtual QChartSeriesType type() const = 0;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif

