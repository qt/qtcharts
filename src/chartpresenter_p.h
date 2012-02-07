#ifndef CHARTPRESENTER_H_
#define CHARTPRESENTER_H_

#include "qchartglobal.h"
#include <QRectF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class QChartSeries;
class ChartDataSet;
class QChart;
class Domain;
class QXYChartSeries;
class XYLineChartItem;

class ChartPresenter: public QObject
{
    Q_OBJECT
public:
    ChartPresenter(QChart* chart,ChartDataSet *dataset);
    virtual ~ChartPresenter();

private:
    void creteConnections();

public slots:
    void handleSeriesAdded(QChartSeries* series);
    void handleSeriesRemoved(QChartSeries* series){};
    void handleSeriesChanged(QChartSeries* series);
    //void handleDomainChanged(Domain oldDomain,Domain newDomain);
    void handleGeometryChanged();



private:
    QMap<QChartSeries*,ChartItem*> m_chartItems;
    QChart* m_chart;
    ChartDataSet* m_dataset;
    QRectF m_rect;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
