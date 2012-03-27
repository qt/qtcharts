#ifndef PERCENTBARSERIES_H
#define PERCENTBARSERIES_H

#include <QStringList>
#include <qbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QPercentBarSeries : public QBarSeries
{
    Q_OBJECT
public:
    QPercentBarSeries(QStringList categories, QObject *parent = 0);
    virtual QSeriesType type() const { return QSeries::SeriesTypePercentBar; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PERCENTBARSERIES_H
