#ifndef PERCENTBARCHARTSERIES_H
#define PERCENTBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PercentBarGroup;
class QBarCategory;
class QBarSet;
class BarChartModel;

class QTCOMMERCIALCHART_EXPORT PercentBarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    PercentBarChartSeries(QBarCategory &category, QObject* parent=0);

    // from BarChartSeriesBase
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypePercentBar; }

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

    PercentBarGroup* mPercentBarGroup;
    BarChartModel* mModel;

};

QTCOMMERCIALCHART_END_NAMESPACE


#endif // PERCENTBARCHARTSERIES_H
