#ifndef CHARTTHEME_H
#define CHARTTHEME_H

#include "qchartglobal.h"
#include "qchart.h"
#include <QColor>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class QChartSeries;
class LineChartItem;
class QLineChartSeries;
class BarPresenter;
class QBarChartSeries;
class StackedBarPresenter;
class QStackedBarChartSeries;
class QPercentBarChartSeries;
class PercentBarPresenter;
class QScatterSeries;
class ScatterPresenter;
class PiePresenter;
class QPieSeries;
class SplinePresenter;
class QSplineSeries;

class ChartTheme
{
protected:
    explicit ChartTheme(QChart::ChartTheme id =  QChart::ChartThemeDefault);
public:
    static ChartTheme* createTheme(QChart::ChartTheme theme);
    QChart::ChartTheme id() const {return m_id;}
    void decorate(QChart* chart);
    void decorate(ChartItem* item, QChartSeries* series,int count);
    void decorate(LineChartItem* item, QLineChartSeries*, int count);
    void decorate(BarPresenter* item, QBarChartSeries* series,int count);
    void decorate(StackedBarPresenter* item, QStackedBarChartSeries* series,int count);
    void decorate(PercentBarPresenter* item, QPercentBarChartSeries* series,int count);
    void decorate(ScatterPresenter* presenter, QScatterSeries* series, int count);
    void decorate(PiePresenter* item, QPieSeries* series, int count);
    void decorate(QChartAxis* axis,AxisItem* item);
    void decorate(SplinePresenter* presenter, QSplineSeries* series, int count);

protected:
    QChart::ChartTheme m_id;
    QColor m_gradientStartColor;
    QColor m_gradientEndColor;
    QList<QColor> m_seriesColor;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTHEME_H
