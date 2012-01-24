#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

#include <QList>
#include "qchartseries.h"
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeries : public QChartSeries
{
    // TODO:
//    Q_OBJECT
public:
    BarChartSeries(QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

    virtual bool setData(QList<int> data);
    virtual bool setData(QList<qreal> data) {return false;}
    virtual bool setData(QList<qreal> x, QList<qreal> y) {return false;}


    // Methods to find out minimum and maximum values of data
    int min();
    int max();
    int count();
    int valueAt(int i);

private:

    QList<int> mData;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
