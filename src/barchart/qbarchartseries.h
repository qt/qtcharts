#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

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

    void addBarSet(QBarSet *set);               // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    int countSets();
    int countCategories();
    QBarSet* nextSet(bool getFirst=false);      // Returns first set, if called with true
    QBarSet *setAt(int index);

    QList<QString> legend();                    // Returns legend of series (ie. names of all sets in series)

public:
    // TODO: Functions below this are not part of api and will be moved
    // to private implementation, when we start using it
    // TODO: TO PIMPL --->
    QString label(int category);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal maxCategorySum();
    BarChartModel& model();
    // <--- TO PIMPL

signals:
    void changed(int index);

    // TODO: internal signals, these to private implementation.
    // TODO: TO PIMPL --->
    void floatingValuesEnabled(bool enabled);
    void toolTipEnabled(bool enabled);
    void separatorsEnabled(bool enabled);
    void showToolTip(QPoint pos, QString tip);
    // <--- TO PIMPL

public Q_SLOTS:
    void enableFloatingValues(bool enabled=true);    // enables floating values on top of bars
    void enableToolTip(bool enabled=true);           // enables tooltips
    void enableSeparators(bool enabled=true);        // enables separators between categories

protected:
    BarChartModel* mModel;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
