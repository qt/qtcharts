#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarCategory;
class QBarSet;
class BarChartModel;

// Container for series
class QTCOMMERCIALCHART_EXPORT QBarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    QBarChartSeries(QBarCategory *category, QObject* parent=0);

    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

    void addBarSet(QBarSet *set);       // Takes ownership of set
    void removeBarSet(QBarSet *set);    // Removes set, releases ownership.
    int countSets();
    QBarSet* nextSet(bool getFirst=false);     // Returns first set, if called with true

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

    BarChartModel* mModel;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
