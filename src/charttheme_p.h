#ifndef CHARTTHEME_H
#define CHARTTHEME_H

#include "qchartglobal.h"
#include "qchart.h"
#include <QColor>
#include <QGradientStops>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class QSeries;
class LineChartItem;
class QLineSeries;
class BarPresenter;
class QBarSeries;
class StackedBarPresenter;
class QStackedBarSeries;
class QPercentBarSeries;
class PercentBarPresenter;
class QScatterSeries;
class ScatterChartItem;
class PiePresenter;
class QPieSeries;
class SplineChartItem;
class QSplineSeries;
class AreaChartItem;
class QAreaSeries;

class ChartTheme
{
public:
    enum BackgroundShadesMode {
        BackgroundShadesNone = 0,
        BackgroundShadesVertical,
        BackgroundShadesHorizontal,
        BackgroundShadesBoth
    };

protected:
    explicit ChartTheme(QChart::ChartTheme id =  QChart::ChartThemeDefault);
public:
    static ChartTheme* createTheme(QChart::ChartTheme theme);
    QChart::ChartTheme id() const {return m_id;}
    void decorate(QChart* chart);
    void decorate(QLegend* legend);
    //void decorate(ChartItem* item, QSeries* series,int index);
    void decorate(BarPresenter* item, QBarSeries* series, int index);
    void decorate(StackedBarPresenter* item, QStackedBarSeries* series, int index);
    void decorate(PercentBarPresenter* item, QPercentBarSeries* series, int index);
    void decorate(LineChartItem* item, QLineSeries* series, int index);
    void decorate(AreaChartItem* item, QAreaSeries* series, int index);
    void decorate(ScatterChartItem* presenter, QScatterSeries* series, int index);
    void decorate(PiePresenter* item, QPieSeries* series, int index);
    void decorate(SplineChartItem* presenter, QSplineSeries* series, int index);
    void decorate(QChartAxis* axis, AxisItem* item);

public: // utils
    void generateSeriesGradients();
    static QColor colorAt(const QColor &start, const QColor &end, qreal pos);
    static QColor colorAt(const QGradient &gradient, qreal pos);

protected:
    QChart::ChartTheme m_id;
    QList<QColor> m_seriesColors;
    QList<QGradient> m_seriesGradients;
    QLinearGradient m_backgroundGradient;

    QFont m_masterFont;
    QPen m_axisLinePen;
    QBrush m_axisLabelBrush;
    QPen m_axisLabelPen;
    QPen m_backgroundShadesPen;
    QBrush m_backgroundShadesBrush;
    BackgroundShadesMode m_backgroundShades;
    QPen m_gridLinePen;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTHEME_H
