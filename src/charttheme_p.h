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
class BarGroup;
class BarChartSeries;
class StackedBarGroup;
class StackedBarChartSeries;
class PercentBarChartSeries;
class PercentBarGroup;
class QScatterSeries;
class ScatterPresenter;
class PiePresenter;
class QPieSeries;

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
    void decorate(BarGroup* item, BarChartSeries* series,int count);
    void decorate(StackedBarGroup* item, StackedBarChartSeries* series,int count);
    void decorate(PercentBarGroup* item, PercentBarChartSeries* series,int count);
    void decorate(ScatterPresenter* presenter, QScatterSeries* series, int count);
    void decorate(PiePresenter* item, QPieSeries* series, int count);
    void decorate(QChartAxis& axis,AxisItem* item);

protected:
    QChart::ChartTheme m_id;
    QColor m_gradientStartColor;
    QColor m_gradientEndColor;
    QList<QColor> m_seriesColor;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTHEME_H
