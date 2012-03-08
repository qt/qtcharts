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
protected:
    explicit ChartTheme(QChart::ChartTheme id =  QChart::ChartThemeDefault);
public:
    static ChartTheme* createTheme(QChart::ChartTheme theme);
    QChart::ChartTheme id() const {return m_id;}
    void decorate(QChart* chart);
    void decorate(ChartItem* item, QSeries* series,int count);
    void decorate(BarPresenter* item, QBarSeries* series,int count);
    void decorate(StackedBarPresenter* item, QStackedBarSeries* series,int count);
    void decorate(PercentBarPresenter* item, QPercentBarSeries* series,int count);
    void decorate(LineChartItem* item, QLineSeries* series,int count);
    void decorate(AreaChartItem* item, QAreaSeries* series,int count);
    void decorate(ScatterChartItem* presenter, QScatterSeries* series, int count);
    void decorate(PiePresenter* item, QPieSeries* series, int count);
    void decorate(QChartAxis* axis,AxisItem* item);
    void decorate(SplineChartItem* presenter, QSplineSeries* series, int count);

public: // utils
    void generateSeriesGradients();
    static QColor colorAt(const QColor &start, const QColor &end, qreal pos);
    static QColor colorAt(const QGradient &gradient, qreal pos);

protected:
    QChart::ChartTheme m_id;
    QList<QColor> m_seriesColors;
    QList<QGradient> m_seriesGradients;
    QLinearGradient m_backgroundGradient;

    // TODO: Add something like the following to themes:
//    QPen axisLinePen;
//    QPen backgroundHorizontalGridPen;
//    QPen backgroundVerticalGridPen;
//    // FillAll, FillEverySecondRow, FillEverySecondColumn, FillEverySecondRowAndColumn, FillNone
//    int backgroundType;
//    QFont masterFont;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTHEME_H
