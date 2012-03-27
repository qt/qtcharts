#ifndef QCHART_H
#define QCHART_H

#include <QSeries>
#include <QGraphicsWidget>

class QGraphicsSceneResizeEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Axis;
class QSeries;
class QChartAxis;
class QLegend;
class QChartPrivate;

class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum ChartTheme {
        ChartThemeDefault,
        ChartThemeLight,
        ChartThemeBlueCerulean,
        ChartThemeDark,
        ChartThemeBrownSand,
        ChartThemeBlueNcs,
        ChartThemeIcy,
        ChartThemeScientific,
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

    void addSeries(QSeries *series, QChartAxis *axisY = 0);
    void removeSeries(QSeries *series);
    void removeAllSeries();

    void setTheme(QChart::ChartTheme theme);
    QChart::ChartTheme theme() const;

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
    void scrollLeft();
    void scrollRight();
    void scrollUp();
    void scrollDown();

    QChartAxis* axisX() const;
    QChartAxis* axisY() const;

    QLegend& legend() const;
    QLegend* takeLegend();
    void giveLegend(QLegend* legend);

    int padding() const;

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

protected:
    QScopedPointer<QChartPrivate> d_ptr;

private:
    void setPadding(int padding);
    void setBackgroundPadding(int padding);
    void setBackgroundDiameter(int diameter);

private:
    Q_DISABLE_COPY(QChart);
};

QTCOMMERCIALCHART_END_NAMESPACE

Q_DECLARE_OPERATORS_FOR_FLAGS(QTCOMMERCIALCHART_NAMESPACE::QChart::AnimationOptions)

#endif
