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
    void addDomain(const QRectF& rect, const QRectF& viewport);
    bool nextDomain();
    bool previousDomain();
    void clearDomains(int toIndex =0);
    const Domain domain(QChartAxis *axisY) const;
    int domainIndex() const {return m_domainIndex;}
    void setDomain(int index);

    QChartAxis* axisX() const { return m_axisX;};
    QChartAxis* axisY(QSeries* series = 0) const;

signals:
    void seriesAdded(QSeries* series);
    void seriesRemoved(QSeries* series);
    void axisAdded(QChartAxis* axis);
    void axisRemoved(QChartAxis* axis);
    void axisRangeChanged(QChartAxis* axis, const QStringList& labels);
    void seriesDomainChanged(QSeries* series,const Domain& domain);

private slots:
	void handleRangeChanged(QChartAxis*);
	void handleTickChanged(QChartAxis*);

private:
    QStringList createLabels(QChartAxis* axis,qreal min, qreal max);

private:
    QMultiMap<QChartAxis*, Domain> m_domainMap;
    QMultiMap<QChartAxis*, QSeries*> m_seriesMap;
    QChartAxis* m_axisX;
    QChartAxis* m_axisY;
    int m_domainIndex;
    bool m_axisXInitialized;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTENGINE_P_H_ */
