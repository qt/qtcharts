#ifndef CHARTPRESENTER_H_
#define CHARTPRESENTER_H_

#include "qchartglobal.h"
#include "qchart.h" //becouse of QChart::ChartThemeId //TODO
#include "qchartaxis.h"
#include <QRectF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class QSeries;
class ChartDataSet;
//class QChart;
class Domain;
class AxisItem;
class ChartTheme;

class ChartPresenter: public QObject
{
    Q_OBJECT
public:
    enum ZValues {
        BackgroundZValue = -1,
        ShadesZValue,
        GridZValue,
        AxisZValue,
        LineChartZValue,
        ScatterSeriesZValue
    };

    ChartPresenter(QChart* chart,ChartDataSet *dataset);
    virtual ~ChartPresenter();

    void setMargin(int margin);
    int margin() const;

    QRectF geometry() const;

    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme();

    void setAnimationOptions(QChart::AnimationOptions options);
    QChart::AnimationOptions animationOptions() const;

private:
    void createConnections();

public slots:
    void handleSeriesAdded(QSeries* series);
    void handleSeriesRemoved(QSeries* series);
    void handleAxisAdded(QChartAxis* axis);
    void handleAxisRemoved(QChartAxis* axis);
    void handleSeriesDomainChanged(QSeries* series, const Domain& domain);
    void handleAxisLabelsChanged(QChartAxis* axis, const QStringList& labels);
    void handleGeometryChanged();
signals:
    void geometryChanged(const QRectF& rect);
private:
    QMap<QSeries*,ChartItem*> m_chartItems;
    QMap<QChartAxis*,AxisItem*> m_axisItems;
    QChart* m_chart;
    ChartDataSet* m_dataset;
    ChartTheme *m_chartTheme;
    int m_marginSize;
    QRectF m_rect;
    QChart::AnimationOptions m_options;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
