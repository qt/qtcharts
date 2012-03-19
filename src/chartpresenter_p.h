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
class Domain;
class AxisItem;
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
    ChartAnimator* animator() const {return m_animator;};

    void setChartTheme(QChart::ChartTheme theme,bool force = true);
    QChart::ChartTheme chartTheme();

    void setAnimationOptions(QChart::AnimationOptions options);
    QChart::AnimationOptions animationOptions() const;

    void zoomIn();
    void zoomIn(const QRectF& rect);
    void zoomOut();
    void zoomReset();
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
    int m_zoomIndex;
    QMap<QSeries*,ChartItem*> m_chartItems;
    QMap<QChartAxis*,AxisItem*> m_axisItems;
    QVector<QRectF> m_zoomStack;
    QRectF m_rect;
    QChart::AnimationOptions m_options;
    bool m_themeForce;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
