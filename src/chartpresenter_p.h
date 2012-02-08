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
/*
    void setAxisX(const QChartAxis& axis);
    void setAxisY(const QChartAxis& axis);
    void setAxisY(const QList<QChartAxis>& axis);


*/

    void setMargin(int margin);
    int margin() const;

    void zoomInToRect(const QRectF& rectangle);
    void zoomIn();
    void zoomOut();
    void zoomReset();

private:
    void creteConnections();

public slots:
    void handleSeriesAdded(QChartSeries* series);
    void handleSeriesRemoved(QChartSeries* series){};
    void handleSeriesChanged(QChartSeries* series);
    //void handleDomainChanged(Domain oldDomain,Domain newDomain);
    void handleGeometryChanged();

signals:
    void geometryChanged(const QRectF& rect);

private:
    QMap<QChartSeries*,ChartItem*> m_chartItems;
    QChart* m_chart;
    ChartDataSet* m_dataset;
    QVector<Domain> m_domains;
    int m_domainIndex;
    int m_marginSize;
    QRectF m_rect;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
