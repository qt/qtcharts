#ifndef QHORIZONTALBARSERIES_H
#define QHORIZONTALBARSERIES_H

#include <qabstractbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QHorizontalBarSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QHorizontalBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalBarSeries(QObject *parent = 0);
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QHorizontalBarSeries)
    Q_DISABLE_COPY(QHorizontalBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHORIZONTALBARSERIES_H
