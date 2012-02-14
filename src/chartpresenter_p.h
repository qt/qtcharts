#ifndef CHARTPRESENTER_H_
#define CHARTPRESENTER_H_

#include "qchartglobal.h"
#include "qchart.h" //becouse of QChart::ChartThemeId //TODO
#include "qchartaxis.h"
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

    void setDefaultAxisX(const QChartAxis& axis);
    void setDefaultAxisY(const QChartAxis& axis);
    QChartAxis defaultAxisX() const;
    QChartAxis defaultAxisY() const;
    QChartAxis axisY(int id) const;
    int addAxisY(const QChartAxis& axis);
    void removeAxisY(int id);

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
    QMap<int,AxisItem*> m_axisItems;
    QMap<int,QChartAxis> m_axis;
    QChart* m_chart;
    ChartDataSet* m_dataset;
    QVector<Domain> m_domains;
    ChartTheme *m_chartTheme;
    QChartAxis m_axisX;
    AxisItem* m_axisXItem;
    QChartAxis m_axisY;
    AxisItem* m_axisYItem;
    int m_domainIndex;
    int m_marginSize;
    QRectF m_rect;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
