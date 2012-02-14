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
    BarChartSeries(QBarCategory &category, QObject* parent=0);

    // from BarChartSeriesBase
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

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

    BarGroup* mBarGroup;
    BarChartModel* mModel;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
