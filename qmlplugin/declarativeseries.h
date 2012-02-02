#ifndef DECLARATIVESERIES_H
#define DECLARATIVESERIES_H

#include <QDeclarativeItem>
#include <qchart.h>
#include <qchartseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeSeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_ENUMS(SeriesType)
    Q_PROPERTY(SeriesType seriesType READ seriesType WRITE setSeriesType)

public:
    // TODO: how to re-use the existing enum from QChart?
    enum SeriesType {
        SeriesTypeInvalid = QChartSeries::SeriesTypeInvalid,
        SeriesTypeLine,
//        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter
//        SeriesTypeSpline
    };

    explicit DeclarativeSeries(QDeclarativeItem *parent = 0);

signals:

public slots:
    void setParentForSeries();

public: // from QDeclarativeItem
    QVariant itemChange(GraphicsItemChange, const QVariant &);

public:
    void setSeriesType(SeriesType type);
    SeriesType seriesType() { return m_seriesType; }

private:
    void initSeries();
    SeriesType m_seriesType;
    QChart *m_chart;
    QChartSeries *m_series;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESERIES_H
