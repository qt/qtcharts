#ifndef CHARTDATASET_P_H_
#define CHARTDATASET_P_H_

#include "qchartseries.h"
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

    void addSeries(QChartSeries* series,QChartAxis *axisY = 0);
    void removeSeries(QChartSeries* series);
    void addDomain(const QRectF& rect, const QRectF& viewport);
    bool nextDomain();
    bool previousDomain();
    void clearDomains(int toIndex =0);
    const Domain domain(QChartAxis *axisY) const;
    int domainIndex() const {return m_domainIndex;}

    QChartAxis* axisX() const { return m_axisX;};
    QChartAxis* axisY(QChartSeries* series = 0) const;

signals:
    void seriesAdded(QChartSeries* series);
    void seriesRemoved(QChartSeries* series);
    void axisAdded(QChartAxis* axis);
    void axisRemoved(QChartAxis* axis);
    void axisLabelsChanged(QChartAxis* axis, const QStringList& labels);
    void seriesDomainChanged(QChartSeries* series,const Domain& domain);

private slots:
	void handleMinChanged(qreal min);
	void handleMaxChanged(qreal max);
	void handleTickChanged(QChartAxis*);

private:
    void setDomain(int index);
    QStringList createLabels(QChartAxis* axis,qreal min, qreal max);

private:
    QMultiMap<QChartAxis*, Domain> m_domainMap;
    QMultiMap<QChartAxis*, QChartSeries*> m_seriesMap;
    QChartAxis* m_axisX;
    QChartAxis* m_axisY;
    int m_domainIndex;
    bool m_axisXInitialized;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTENGINE_P_H_ */
