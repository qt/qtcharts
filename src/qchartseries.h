#ifndef QCHARTSERIES_H
#define QCHARTSERIES_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QChartSeries : public QObject
{
    //TODO:
    //Q_OBJECT
public:
    enum QChartSeriesType {
        SeriesTypeLine = 0,
//        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypePie,
        SeriesTypeScatter
//        SeriesTypeSpline
    };

protected:
    QChartSeries(QObject *parent = 0):QObject(parent){};

public:
    virtual ~QChartSeries(){};

    // Factory method
    static QChartSeries* create(QChartSeriesType type, QObject* parent = 0 );

    // Pure virtual
    virtual QChartSeriesType type() const = 0;

    virtual bool setData(QList<int> data) { return false; }
    virtual bool setData(QList<qreal> data) { return false; }
    virtual bool setData(QList<qreal> x, QList<qreal> y){ return false; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif

