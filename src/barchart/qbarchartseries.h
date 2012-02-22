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
// TODO: derive Stacked and percent bar charts from this?
class QTCOMMERCIALCHART_EXPORT QBarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    QBarChartSeries(QBarCategory *category, QObject* parent=0);

    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

    void addBarSet(QBarSet *set);               // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    int countSets();
    QBarSet* nextSet(bool getFirst=false);     // Returns first set, if called with true

    QList<QString> legend();  // Returns legend of series (ie. names of all sets in series)

    // Disabled by default. Call these to change behavior.
    void enableFloatingValues(bool enabled=true);
    void enableHoverNames(bool enabled=true);

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

    // TODO: these to private implementation.
    void floatingValuesEnabled(bool enabled);
    void hoverNamesEnabled(bool enabled);


//public Q_SLOTS:

private:
    BarChartModel* mModel;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
