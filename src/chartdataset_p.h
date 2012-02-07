#ifndef CHARTENGINE_P_H_
#define CHARTENGINE_P_H_

#include <qchartseries.h>
#include "domain_p.h"
#include <QVector>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartDataSet : public QObject
{
    Q_OBJECT
public:
    ChartDataSet(QObject* parent =0);
    virtual ~ChartDataSet();

    void addSeries(QChartSeries* series);
    const Domain& domain() const;

signals:
    void seriesAdded(QChartSeries* series);
    void domainChanged();

private:
    QList<QChartSeries*> m_chartSeries;
    QVector<Domain> m_domains;
    int m_domainIndex;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTENGINE_P_H_ */
