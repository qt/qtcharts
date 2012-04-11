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

#ifndef CHARTPRESENTER_H
#define CHARTPRESENTER_H

#include "qchartglobal.h"
#include "chartbackground_p.h" //TODO fix me
#include "qchart.h" //becouse of QChart::ChartThemeId //TODO
#include "qchartaxis.h"
#include <QRectF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Chart;
class QAbstractSeries;
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

    void setGeometry(const QRectF& rect);
    QRectF chartGeometry() const { return m_chartRect; }

    void setMinimumMarginHeight(Axis* axis, qreal height);
    void setMinimumMarginWidth(Axis* axis, qreal width);
    qreal minimumLeftMargin() const { return m_minLeftMargin; }
    qreal minimumBottomMargin() const { return m_minBottomMargin; }

public: //TODO: fix me
    void resetAllElements();
    void createChartBackgroundItem();
    void createChartTitleItem();
    QRectF margins() const { return m_chartMargins;}

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries* series,Domain* domain);
    void handleSeriesRemoved(QAbstractSeries* series);
    void handleAxisAdded(QChartAxis* axis,Domain* domain);
    void handleAxisRemoved(QChartAxis* axis);
    void updateLayout();

Q_SIGNALS:
    void geometryChanged(const QRectF& rect);


private:
    QChart* m_chart;
    ChartAnimator* m_animator;
    ChartDataSet* m_dataset;
    ChartTheme *m_chartTheme;
    QMap<QAbstractSeries *, Chart *> m_chartItems;
    QMap<QChartAxis *, Axis *> m_axisItems;
    QRectF m_rect;
    QRectF m_chartRect;
    QChart::AnimationOptions m_options;
    qreal m_minLeftMargin;
    qreal m_minBottomMargin;
public: //TODO: fixme
    ChartBackground* m_backgroundItem;
    QGraphicsSimpleTextItem* m_titleItem;
    int m_marginBig;
    int m_marginSmall;
    int m_marginTiny;
    QRectF m_chartMargins;
    QRectF m_legendMargins;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H_ */
