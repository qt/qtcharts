#ifndef CHARTPRESENTER_H_
#define CHARTPRESENTER_H_

#include "qchartglobal.h"
#include "qchart.h" //becouse of QChart::ChartThemeId //TODO
#include "qchartaxis.h"
#include <QRectF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Chart;
class QSeries;
class ChartDataSet;
class Domain;
class Axis;
class ChartTheme;
class ChartAnimator;

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
        BarSeriesZValue,
        ScatterSeriesZValue,
        PieSeriesZValue,
        LegendZValue
    };

    ChartPresenter(QChart* chart,ChartDataSet *dataset);
    virtual ~ChartPresenter();

    void setMargin(int margin);
    int margin() const;

    QRectF geometry() const;

    ChartAnimator* animator() const {return m_animator;}
    ChartTheme *theme() { return m_chartTheme; }
    ChartDataSet *dataSet() { return m_dataset; }

    void setChartTheme(QChart::ChartTheme theme,bool force = true);
    QChart::ChartTheme chartTheme();

    void setAnimationOptions(QChart::AnimationOptions options);
    QChart::AnimationOptions animationOptions() const;

    QGraphicsItem* rootItem() const {return m_chart;};

    void zoomIn();
    void zoomIn(const QRectF& rect);
    void zoomOut();
    void scroll(int dx,int dy);

private:
    void createConnections();
    void resetAllElements();

public slots:
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);
    void handleAxisAdded(QChartAxis* axis,Domain* domain);
    void handleAxisRemoved(QChartAxis* axis);
    void handleGeometryChanged();

signals:
    void geometryChanged(const QRectF& rect);

private:
    QChart* m_chart;
    ChartAnimator* m_animator;
    ChartDataSet* m_dataset;
    ChartTheme *m_chartTheme;
    QMap<QSeries*,Chart*> m_chartItems;
    QMap<QChartAxis*,Axis*> m_axisItems;
    QRectF m_rect;
    QChart::AnimationOptions m_options;
    bool m_themeForce;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
