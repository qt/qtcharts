#ifndef QSERIES_H
#define QSERIES_H

#include "qchartglobal.h"
#include <QObject>
#include <QAbstractItemModel>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QSeries : public QObject
{
    Q_OBJECT
public:
    enum QSeriesType {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline
    };

    // Helper class to contain legend and color for it
    // TODO: This as private class?
    class Legend {
    public:
        QString mName;
        QPen mPen;
    };

protected:
    QSeries(QObject *parent = 0) : QObject(parent) {}

public:
    virtual ~QSeries() {}
    virtual QSeriesType type() const = 0;
    // TODO
    virtual bool setModel(QAbstractItemModel* /*model*/) { return false; }

    virtual QList<QSeries::Legend> legend() { QList<QSeries::Legend> l; return l; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
