#ifndef CHARTPRESENTER_H_
#define CHARTPRESENTER_H_

#include "qchartglobal.h"
#include "qchart.h" //becouse of QChart::ChartThemeId //TODO
#include <QRectF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class QChartSeries;
class ChartDataSet;
//class QChart;
class Domain;
class AxisItem;
class ChartTheme;

class ChartPresenter: public QObject
{
    Q_OBJECT
public:
    ChartPresenter(QChart* chart,ChartDataSet *dataset);
    virtual ~ChartPresenter();

    void setMargin(int margin);
    int margin() const;

    void zoomInToRect(const QRectF& rectangle);
    void zoomIn();
    void zoomOut();
    void zoomReset();

    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme();

    QChartAxis* axisX();
    QChartAxis* axisY();
    QChartAxis* addAxisX();
    QChartAxis* addAxisY();
    void removeAxis(QChartAxis* axis);

private:
    void createConnections();

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
    QMap<QChartAxis*,AxisItem*> m_axisItems;
    QChart* m_chart;
    ChartDataSet* m_dataset;
    QVector<Domain> m_domains;
    ChartTheme *m_chartTheme;
    QChartAxis* m_axisX;
    QChartAxis* m_axisY;
    int m_domainIndex;
    int m_marginSize;
    QRectF m_rect;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
