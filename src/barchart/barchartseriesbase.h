#ifndef BARCHARTSERIESBASE_H
#define BARCHARTSERIESBASE_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class BarGroupBase;
class BarChartModel;

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeriesBase : public QChartSeries
{
    Q_OBJECT
protected:
    BarChartSeriesBase(QObject* parent=0);

public:
    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeInvalid; }

    // TODO: << operator for convinience
    // Returns id for vector.
    int addData(QList<qreal> data);
    void removeData(int id);

    qreal min();
    qreal max();
    int countColumns();     // Count items in one series.
    qreal valueAt(int series, int item);
    qreal maxColumnSum();

    BarChartModel& model();

signals:
    void changed(int index);

public Q_SLOTS:

private:

    BarChartModel& mModel;
    BarGroupBase* mBarGroup;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIESBASE_H
