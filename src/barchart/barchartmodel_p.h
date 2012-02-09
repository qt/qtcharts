#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QObject>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Model for bar chart. Internal class.
// TODO: Implement as QAbstractItemModel?

class BarChartModel : public QObject //, public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BarChartModel(QObject *parent = 0);
    ~BarChartModel();
    
    // Adds data to model. returns id.
    int addData(QList<qreal> data);
    void removeData(int id);

    int countRows();            // Number of series in model
    int countColumns();         // Maximum number of items in series
    int countTotalItems();      // Total items in all series. Includes empty items.

    // TODO: qreal these
    int max();  // Maximum value of all series
    int min();  // Minimum value of all series
    qreal valueAt(int series, int item);

    qreal columnSum(int column);
    qreal maxColumnSum();   // returns maximum sum of items in all columns.

signals:
    void modelUpdated();

public slots:
    
private:

    // Little helper class.
    class DataContainer {
        public:
            DataContainer(QList<qreal> data, int id) : mId(id), mData(data) {}
            int countColumns() { return mData.count(); }
            qreal valueAt(int item) { return mData.at(item); }

            int mId; // TODO: Is this needed?
        private:
            QList<qreal> mData;
    };

    // Owned. N series. each has a list of values.
    QList<DataContainer*> mDataModel;
    int mRunningId;
    int mMaxColumns;    // longest series in datamodel

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTMODEL_H
