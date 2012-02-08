#ifndef BARCHARTSERIESBASE_H
#define BARCHARTSERIESBASE_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"
#include "qchartglobal.h"

class BarGroupBase;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeriesBase : public QChartSeries
{
    Q_OBJECT
protected:
    BarChartSeriesBase(QObject* parent=0);

public:
    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeInvalid; }

    // TODO: Better data model?
//    virtual bool setModel(QAbstractItemModel* model);
    virtual bool setData(QList<qreal>& data);

    // Methods to find out minimum and maximum values of data
//    int min(); // TODO: remove
//    int max(); // TODO: remove
//    int maxColumnSum();   // TODO: move to model. returns maximum sum of items in all columns.

//    int countRows();    // TODO: remove.
//    int countColumns();     // TODO: remove. Count items in one series.
//    int countTotalItems();  // TODO: move to model
//    int valueAt(int row, int column);   // TODO: move to model

//    int columnSum(int column);  // TODO: move to model

    qreal min();
    qreal max();
    int countValues();
    qreal valueAt(int item);

public Q_SLOTS:

private:

    QAbstractItemModel* mModel;
    BarGroupBase* mBarGroup;

    QList<qreal>* mData;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIESBASE_H
