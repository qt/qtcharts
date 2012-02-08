#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QObject>
#include "barchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Model for bar chart.
// TODO: Implement as QAbstractItemModel?

class BarChartModel : public QObject //, public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BarChartModel(QObject *parent = 0);
    
    // Takes reference, Series are owned by QChart or model?
    void addSeries(BarChartSeriesBase& series);
    void removeSeries(BarChartSeriesBase& series);

    int countSeries();          // Number of series in model
    int countItemsInSeries();   // Maximum number of items in series
    int countTotalItems();      // Total items in all series. Includes empty items.

    int max();  // Maximum value of all series
    int min();  // Minimum value of all series
    qreal valueAt(int series, int item);

signals:
    void modelUpdated();

public slots:
    
private:

    // Data
    QList<BarChartSeriesBase*> mSeries;

    BarChartModel* mSingle;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTMODEL_H
