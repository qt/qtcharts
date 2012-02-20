#ifndef CHART_H
#define CHART_H

#include <qchartglobal.h>
#include <qchartseries.h>
#include <QGraphicsWidget>
#include <QLinearGradient>
#include <QFont>

class QGraphicsSceneResizeEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisItem;
class QChartSeries;
class PlotDomain;
class BarPresenter;
class QChartAxis;
class ChartTheme;
class ChartItem;
class ChartDataSet;
class ChartPresenter;

// TODO: We don't need to have QChart tied to QGraphicsItem:
//class QTCOMMERCIALCHART_EXPORT QChart
//class QTCOMMERCIALCHART_EXPORT QChartGraphicsItem : public QGraphicsItem {
// public: QChartGraphicsItem(QChart &chart);

/*!
 * TODO: define the responsibilities
 */
class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum ChartTheme {
        /*! The default theme follows the GUI style of the Operating System */
        ChartThemeDefault,
        ChartThemeVanilla,
        ChartThemeIcy,
        ChartThemeGrayscale,
        ChartThemeScientific,
        //ChartThemeUnnamed1
    };

public:
    QChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~QChart();

    void addSeries(QChartSeries* series);

    //TODO: QChartSeries* createSeries(QSeriesData *data, QChartSeries::QChartSeriesType type);
    // TODO: who owns the series now? maybe owned by chart and returned a reference instead...
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

    void setMargin(int margin);
    int margin() const;
    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme() const;

    void setChartTitle(const QString& title);
    void setChartTitleFont(const QFont& font);
    void setChartBackgroundBrush(const QBrush& brush);
    void setChartBackgroundPen(const QPen& pen);

    void zoomInToRect(const QRectF& rectangle);
    void zoomIn();
    void zoomOut();
    void zoomReset();

    void setDefaultAxisX(const QChartAxis& axis);
    void setDefaultAxisY(const QChartAxis& axis);
    QChartAxis defaultAxisX() const;
    QChartAxis defaultAxisY() const;
    QChartAxis axisY(int id) const;
    int addAxisY(const QChartAxis& axis);
    void removeAxisY(int id);

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    Q_DISABLE_COPY(QChart)
    QGraphicsRectItem* m_backgroundItem;
    QGraphicsTextItem* m_titleItem;
    QRectF m_rect;
    ChartDataSet *m_dataset;
    ChartPresenter *m_presenter;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
