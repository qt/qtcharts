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

#ifndef CHARTPRESENTER_H_
#define CHARTPRESENTER_H_

#include "qchartglobal.h"
#include "qchart.h" //becouse of QChart::ChartThemeId //TODO
#include "qchartaxis.h"
#include <QRectF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Chart;
class QSeries;
class ChartDataSet;
class Domain;
class Axis;
class ChartTheme;
class ChartAnimator;

class ChartPresenter: public QObject
{
    Q_OBJECT
public:
    enum ZValues {
        BackgroundZValue = -1,
        ShadesZValue,
        GridZValue,
        LineChartZValue,
        BarSeriesZValue,
        ScatterSeriesZValue,
        PieSeriesZValue,
        AxisZValue,
        LegendZValue
    };

    ChartPresenter(QChart* chart,ChartDataSet *dataset);
    virtual ~ChartPresenter();

    int backgroundPadding() const { return m_backgroundPadding; }
    QRectF geometry() const { return m_rect; }
    ChartAnimator* animator() const { return m_animator; }
    ChartTheme *chartTheme() const { return m_chartTheme; }
    ChartDataSet *dataSet() const { return m_dataset; }
    QGraphicsItem* rootItem() const { return m_chart; }

    void setTheme(QChart::ChartTheme theme,bool force = true);
    QChart::ChartTheme theme();

    void setAnimationOptions(QChart::AnimationOptions options);
    QChart::AnimationOptions animationOptions() const;

    void zoomIn();
    void zoomIn(const QRectF& rect);
    void zoomOut();
    void scroll(int dx,int dy);

private:
    void createConnections();
    void resetAllElements();

public Q_SLOTS:
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);
    void handleAxisAdded(QChartAxis* axis,Domain* domain);
    void handleAxisRemoved(QChartAxis* axis);
    void handleGeometryChanged();

Q_SIGNALS:
    void geometryChanged(const QRectF& rect);

private:
    QChart* m_chart;
    ChartAnimator* m_animator;
    ChartDataSet* m_dataset;
    ChartTheme *m_chartTheme;
    QMap<QSeries*,Chart*> m_chartItems;
    QMap<QChartAxis*,Axis*> m_axisItems;
    QRectF m_rect;
    QChart::AnimationOptions m_options;
    bool m_themeForce;
    int m_backgroundPadding;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
