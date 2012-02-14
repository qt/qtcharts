#ifndef STACKEDBARCHARTSERIES_H
#define STACKEDBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarGroup;
class QBarCategory;
class QBarSet;
class BarChartModel;

class QTCOMMERCIALCHART_EXPORT StackedBarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    StackedBarChartSeries(QBarCategory &category, QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeStackedBar; }

    void addBarSet(QBarSet &set);
    void removeBarSet(QBarSet &set);

    int countCategories();
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal maxCategorySum();

    BarChartModel& model();

signals:
    void changed(int index);

public Q_SLOTS:

private:

    StackedBarGroup* mStackedBarGroup;
    BarChartModel* mModel;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTSERIES_H
