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
class ChartBackground;


class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum ChartTheme {
        ChartThemeDefault,
        ChartThemeVanilla,
        ChartThemeIcy,
        ChartThemeGrayscale,
        ChartThemeScientific,
        ChartThemeBlueCerulean,
        ChartThemeLight,
        ChartThemeCount
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

    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme() const;

    void setTitle(const QString& title);
    QString title() const;
    void setTitleFont(const QFont& font);
    QFont titleFont() const;
    void setTitleBrush(const QBrush &brush);
    QBrush titleBrush() const;
    void setBackgroundBrush(const QBrush& brush);
    QBrush backgroundBrush() const;
    void setBackgroundPen(const QPen& pen);
    QPen backgroundPen() const;

    void setBackgroundVisible(bool visible);
    bool isBackgroundVisible() const;

    void setAnimationOptions(AnimationOptions options);
    AnimationOptions animationOptions() const;

    void zoomIn();
    void zoomIn(const QRectF& rect);
    void zoomOut();
    void zoomReset();
    void scrollLeft();
    void scrollRight();
    void scrollUp();
    void scrollDown();

    QChartAxis* axisX() const;
    QChartAxis* axisY() const;

    // TODO: take (and give) legend instead of this.
    QLegend* legend();


    int padding() const;

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    inline void createChartBackgroundItem();
    inline void createChartTitleItem();
    void setPadding(int padding);
    void setBackgroundPadding(int padding);
    void setBackgroundDiameter(int diameter);
    void updateLayout();

private:
    Q_DISABLE_COPY(QChart)
    ChartBackground* m_backgroundItem;
    QGraphicsSimpleTextItem* m_titleItem;
    QRectF m_rect;
    QLegend* m_legend;
    ChartDataSet *m_dataset;
    ChartPresenter *m_presenter;
    int m_padding;
    int m_backgroundPadding;
};

QTCOMMERCIALCHART_END_NAMESPACE

Q_DECLARE_OPERATORS_FOR_FLAGS(QTCOMMERCIALCHART_NAMESPACE::QChart::AnimationOptions)

#endif
