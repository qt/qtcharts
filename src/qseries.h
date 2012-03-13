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
    // TODO: This is actually quite close to current LegendMarker.. combine them?
    class LegendEntry {
        public:
        QString mName;
        QBrush mBrush;
    };

protected:
    QSeries(QObject *parent = 0) : QObject(parent) {}

public:
    virtual ~QSeries() {}
    virtual QSeriesType type() const = 0;
    QString name() { return QString("TODO: Name QSeries"); }
    // TODO
    virtual bool setModel(QAbstractItemModel* /*model*/) { return false; }

    virtual QList<QSeries::LegendEntry> legendEntries() { QList<QSeries::LegendEntry> l; return l; }

    void setTitle(QString title) { m_title = title; }
    QString title() { return m_title; }

private:
    QString m_title;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
