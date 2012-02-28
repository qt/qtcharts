#ifndef STACKEDBARSERIES_H
#define STACKEDBARSERIES_H

#include <QStringList>
#include "qbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QStackedBarSeries : public QBarSeries
{
    Q_OBJECT
public:
    QStackedBarSeries(QStringList categories, QObject* parent=0);

    virtual QSeriesType type() const { return QSeries::SeriesTypeStackedBar; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARSERIES_H
