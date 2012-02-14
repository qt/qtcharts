#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarCategory;
class QBarSet;
class BarGroup;
class BarChartModel;

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    BarChartSeries(QBarCategory *category, QObject* parent=0);

    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

    void addBarSet(QBarSet *set);       // Takes ownership
    void removeBarSet(QBarSet *set);    // Also deletes the set, if set is owned.

    //TODO:
    //QList<QString> legend();  // Returns legend of series (ie. names of all sets in series)

    // TODO: Functions below this are not part of api and will be moved
    // to private implementation, when we start using it (not part of api)
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

    BarGroup* mBarGroup;
    BarChartModel* mModel;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
