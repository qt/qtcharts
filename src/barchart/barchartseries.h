#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

#include <QList>
//#include <QRectF>
#include <QAbstractItemModel>
#include "qchartseries.h"
#include "qchartglobal.h"

// TODO: Can this class be combined with series?
class BarGroup;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    BarChartSeries(QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

    // TODO: Better data model?
    virtual bool setData(QAbstractItemModel* model);

    // Methods to find out minimum and maximum values of data
    int min();
    int max();
    int countSeries();
    int countColumns();     // Count items in one series.
    int countTotalItems();
    int valueAt(int row, int column);

public Q_SLOTS:

    // TODO: wrong place for this... series don't know anything about layout
//    void chartSizeChanged(QRectF rect);

private:

    QAbstractItemModel* mModel;
    BarGroup* mBarGroup;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
