/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

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
class BarChartItem;
class QBarSeries;
class StackedBarChartItem;
class QStackedBarSeries;
class QPercentBarSeries;
class PercentBarChartItem;
class QScatterSeries;
class ScatterChartItem;
class PieChartItem;
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
    void decorate(QChart* chart,bool force = true);
    void decorate(QLegend* legend,bool force = true);
    void decorate(QBarSeries* series, int index,bool force = true);
    void decorate(QLineSeries* series, int index,bool force = true);
    void decorate(QAreaSeries* series, int index,bool force = true);
    void decorate(QScatterSeries* series, int index,bool force = true);
    void decorate(QPieSeries* series, int index,bool force = true);
    void decorate(QSplineSeries* series, int index,bool force = true);
    void decorate(QChartAxis* axis, bool axisX,bool force = true);

public: // utils
    void generateSeriesGradients();
    static QColor colorAt(const QColor &start, const QColor &end, qreal pos);
    static QColor colorAt(const QGradient &gradient, qreal pos);

protected:
    QChart::ChartTheme m_id;
    QList<QColor> m_seriesColors;
    QList<QGradient> m_seriesGradients;
    QLinearGradient m_chartBackgroundGradient;

    QFont m_masterFont;
    QFont m_labelFont;
    QBrush m_titleBrush;
    QPen m_axisLinePen;
    QBrush m_axisLabelBrush;
    QPen m_backgroundShadesPen;
    QBrush m_backgroundShadesBrush;
    BackgroundShadesMode m_backgroundShades;
    QPen m_gridLinePen;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTHEME_H
