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
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline
    };

protected:
    QChartSeries(QObject *parent = 0) : QObject(parent) {}

public:
    virtual ~QChartSeries() {}
    virtual QChartSeriesType type() const = 0;
    // TODO
    virtual bool setModel(QAbstractItemModel* /*model*/) { return false; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
