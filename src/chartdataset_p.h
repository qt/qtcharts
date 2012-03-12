#ifndef CHARTDATASET_P_H_
#define CHARTDATASET_P_H_

#include "qseries.h"
#include "domain_p.h"
#include <QVector>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis;

class ChartDataSet : public QObject
{
    Q_OBJECT
public:
    ChartDataSet(QObject* parent=0);
    virtual ~ChartDataSet();

    void addSeries(QSeries* series,QChartAxis *axisY = 0);
    void removeSeries(QSeries* series);
    void removeAllSeries();

    void zoomInDomain(const QRectF& rect, const QSizeF& size);
    void zoomOutDomain(const QRectF& rect, const QSizeF& size);
    void scrollDomain(int dx,int dy,const QSizeF& size);

    int seriesCount(QSeries::QSeriesType type);
    int seriesIndex(QSeries *series);

    Domain* domain(QSeries* series) const;
    Domain* domain(QChartAxis* axis) const;
    QChartAxis* axis(QSeries* series) const;

    QChartAxis* axisX() const { return m_axisX;};
    QChartAxis* axisY(QSeries* series = 0) const;

signals:
    void seriesAdded(QSeries* series,Domain* domain);
    void seriesRemoved(QSeries* series);
    void axisAdded(QChartAxis* axis,Domain* domain);
    void axisRemoved(QChartAxis* axis);

private:
    QStringList createLabels(QChartAxis* axis,qreal min, qreal max);
    void calculateDomain(QSeries* series,Domain* domain) const;

private:
    QMap<QSeries*, QChartAxis*> m_seriesAxisMap;
    QMap<QChartAxis*, Domain*> m_axisDomainMap;
    QChartAxis* m_axisX;
    QChartAxis* m_axisY;

    int m_domainIndex;
    bool m_axisXInitialized;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTENGINE_P_H_ */
