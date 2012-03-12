#ifndef QCHART_H
#define QCHART_H

#include <qchartglobal.h>
#include <qseries.h>
#include <QGraphicsWidget>
#include <QLinearGradient>
#include <QFont>

class QGraphicsSceneResizeEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisItem;
class QSeries;
class PlotDomain;
class BarPresenter;
class QChartAxis;
class ChartTheme;
class ChartItem;
class ChartDataSet;
class ChartPresenter;
class QLegend;

class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum ChartTheme {
        ChartThemeDefault,
        ChartThemeVanilla,
        ChartThemeIcy,
        ChartThemeGrayscale,
        ChartThemeScientific
        //ChartThemeUnnamed1
        /*! The default theme follows the GUI style of the Operating System */
    };

    enum  AnimationOption {
        NoAnimation = 0x0,
        GridAxisAnimations = 0x1,
        SeriesAnimations =0x2,
        AllAnimations = 0x3
        };
        Q_DECLARE_FLAGS(AnimationOptions, AnimationOption)

public:
    QChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~QChart();

    void addSeries(QSeries* series, QChartAxis* axisY = 0);
    void removeSeries(QSeries* series); //returns ownership , deletes axis if no series attached
    void removeAllSeries(); // deletes series and axis

    void setMargin(int margin);
    int margin() const;
    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme() const;

    void setChartTitle(const QString& title);
    QString chartTitle() const;
    void setChartTitleFont(const QFont& font);
    void setChartTitleBrush(const QBrush &brush);
    QBrush chartTitleBrush();
    void setChartBackgroundBrush(const QBrush& brush);
    void setChartBackgroundPen(const QPen& pen);

    void setAnimationOptions(AnimationOptions options);
    AnimationOptions animationOptions() const;

    void zoomIn();
    void zoomIn(const QRectF& rect);
    void zoomOut();
    void zoomReset();
    void scroll(int dx,int dy);

    QChartAxis* axisX() const;
    QChartAxis* axisY() const;

    QLegend* legend();

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    inline void createChartBackgroundItem();
    inline void createChartTitleItem();
    inline void createLegend();

private:
    Q_DISABLE_COPY(QChart)
    QGraphicsRectItem* m_backgroundItem;
    QGraphicsSimpleTextItem* m_titleItem;
    QRectF m_rect;
    ChartDataSet *m_dataset;
    ChartPresenter *m_presenter;
    QLegend* m_legend;
};

QTCOMMERCIALCHART_END_NAMESPACE

Q_DECLARE_OPERATORS_FOR_FLAGS(QTCOMMERCIALCHART_NAMESPACE::QChart::AnimationOptions)

#endif
