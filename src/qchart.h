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

    void addSeries(QChartSeries* series,QChartAxis* axisY=0);// takes series ownership , takes axis ownership
    void removeSeries(QChartSeries* series); //returns ownership , deletes axis if no series attached
    void removeAllSeries(); // deletes series and axis

    void setMargin(int margin);
    int margin() const;
    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme() const;

    void setChartTitle(const QString& title);
    void setChartTitleFont(const QFont& font);
    void setChartBackgroundBrush(const QBrush& brush);
    void setChartBackgroundPen(const QPen& pen);

    void zoomIn();
    void zoomIn(const QRectF& rect);
    void zoomOut();
    void zoomReset();

    QChartAxis* axisX() const;
    QChartAxis* axisY() const;

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    inline void createChartBackgroundItem();
    inline void createChartTitleItem();

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
