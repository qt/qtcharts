#ifndef BARSERIES_H
#define BARSERIES_H

#include "qseries.h"
#include <QStringList>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSet;
class BarChartModel;

// Container for series
class QTCOMMERCIALCHART_EXPORT QBarSeries : public QSeries
{
    Q_OBJECT
public:
    QBarSeries(QStringList categories, QObject* parent=0);

    virtual QSeriesType type() const { return QSeries::SeriesTypeBar; }

    void addBarSet(QBarSet *set);               // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    int barsetCount();
    int categoryCount();
    QList<QBarSet*> barSets();

    QList<QString> legend();                    // Returns legend of series (ie. names of all sets in series)

public:
    // TODO: Functions below this are not part of api and will be moved
    // to private implementation, when we start using it
    // TODO: TO PIMPL --->
    QBarSet *barsetAt(int index);
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
    void setFloatingValuesEnabled(bool enabled=true);    // enables floating values on top of bars
    void setToolTipEnabled(bool enabled=true);           // enables tooltips
    void setSeparatorsEnabled(bool enabled=true);        // enables separators between categories

protected:
    BarChartModel* mModel;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARSERIES_H
