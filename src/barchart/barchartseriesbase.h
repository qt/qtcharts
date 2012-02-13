#ifndef BARCHARTSERIESBASE_H
#define BARCHARTSERIESBASE_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class BarGroupBase;
class BarChartModel;
class QBarSet;
class QBarCategory;

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeriesBase : public QChartSeries
{
    Q_OBJECT
protected:
//    BarChartSeriesBase(QObject* parent=0);
    BarChartSeriesBase(QBarCategory &category, QObject* parent=0);

public:
    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeInvalid; }

    // TODO: These 3 will be removed.
    int addData(QList<qreal> data);
    void removeData(int id);
    void setLabels(QList<QString> labels);

    // TODO: Expose these to user in derived class instead of here? Common implementation for all bar charts, but not visible to user
    void addBarSet(QBarSet &set);        // Bob[1,5,6,2,15,4] first value goes to category 1 etc..
    void removeBarSet(QBarSet &set);     //

    // These shouldn't be visible to chart series user. However, ChartDataSet needs to access them, and friends are evil.
    qreal min();
    qreal max();
    int countColumns();     // Count items in one series.
    qreal valueAt(int series, int item);
    qreal maxColumnSum();

    BarChartModel& model();
    QString label(int item);

signals:
    void changed(int index);

public Q_SLOTS:

private:

    BarChartModel* mModel;
    QList<QString> mLabels;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIESBASE_H
