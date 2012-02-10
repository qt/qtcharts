#ifndef QCHARTSERIES_H
#define QCHARTSERIES_H

#include "qchartglobal.h"
#include <QObject>
#include <QAbstractItemModel>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QChartSeries : public QObject
{
    Q_OBJECT
public:
    enum QChartSeriesType {
        SeriesTypeInvalid = -1,
        SeriesTypeLine,
//        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter
//        SeriesTypeSpline
    };

protected:
    QChartSeries(QObject *parent = 0):QObject(parent){};

public:
    virtual ~QChartSeries(){};

    // Pure virtual
    virtual QChartSeriesType type() const = 0;

    virtual bool setData(QList<int> /*data*/) { return false; }
    virtual bool setData(QList<qreal> /*data*/) { return false; }
    virtual bool setData(QList<qreal> /*x*/, QList<qreal> /*y*/){ return false; }

    // Prototype for data model. TODO: remove the other setData methods and use something like this for now?
    virtual bool setData(QAbstractItemModel* /*model*/) { return false; }

    // Methods for building a table for bar chart. Call repeatedly to add more than one series
    virtual int addData(QList<qreal> data) {return -1;}
    virtual void removeData(int id) {}
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif

