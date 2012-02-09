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

    void setAxisX(QChartAxis* axis);
    void addAxisY(QChartAxis* axis);
private:
    void createConnections();
    void createDeafultAxis();

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
    QList<AxisItem*> m_axis;
    ChartTheme *m_chartTheme;
    int m_domainIndex;
    int m_marginSize;
    QRectF m_rect;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
