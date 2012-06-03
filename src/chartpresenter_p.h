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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTPRESENTER_H
#define CHARTPRESENTER_H

#include "qchartglobal.h"
#include "qchart.h" //becouse of QChart::ChartThemeId //TODO
#include <QRectF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Chart;
class QAbstractSeries;
class ChartDataSet;
class Domain;
class ChartAxis;
class ChartTheme;
class ChartAnimator;
class ChartBackground;
class ChartAnimation;

class ChartPresenter: public QObject
{
    Q_OBJECT
public:
    enum ZValues {
        BackgroundZValue = -1,
        ShadesZValue,
        GridZValue,
        SeriesZValue,
        LineChartZValue = SeriesZValue,
        BarSeriesZValue = SeriesZValue,
        ScatterSeriesZValue = SeriesZValue,
        PieSeriesZValue = SeriesZValue,
        AxisZValue,
        LegendZValue
    };

    enum State {
        ShowState,
        ScrollUpState,
        ScrollDownState,
        ScrollLeftState,
        ScrollRightState,
        ZoomInState,
        ZoomOutState
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

    void zoomIn(qreal factor);
    void zoomIn(const QRectF& rect);
    void zoomOut(qreal factor);
    void scroll(qreal dx,qreal dy);

    void setGeometry(const QRectF& rect);
    QRectF chartGeometry() const { return m_chartRect; }

    void setMinimumMarginHeight(ChartAxis* axis, qreal height);
    void setMinimumMarginWidth(ChartAxis* axis, qreal width);
    qreal minimumLeftMargin() const { return m_minLeftMargin; }
    qreal minimumBottomMargin() const { return m_minBottomMargin; }

    void startAnimation(ChartAnimation* animation);
    State state() const { return m_state; }
    QPointF statePoint() const { return m_statePoint; }
public: //TODO: fix me
    void resetAllElements();
    void createChartBackgroundItem();
    void createChartTitleItem();
    QRectF margins() const { return m_chartMargins;}

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries* series,Domain* domain);
    void handleSeriesRemoved(QAbstractSeries* series);
    void handleAxisAdded(QAxis* axis,Domain* domain);
    void handleAxisRemoved(QAxis* axis);
    void updateLayout();

private Q_SLOTS:
    void handleAnimationFinished();

Q_SIGNALS:
    void geometryChanged(const QRectF& rect);
    void animationsFinished();

private:
    QChart* m_chart;
    ChartAnimator* m_animator;
    ChartDataSet* m_dataset;
    ChartTheme *m_chartTheme;
    QMap<QAbstractSeries *, Chart *> m_chartItems;
    QMap<QAxis *, ChartAxis *> m_axisItems;
    QRectF m_rect;
    QRectF m_chartRect;
    QChart::AnimationOptions m_options;
    qreal m_minLeftMargin;
    qreal m_minBottomMargin;
    State m_state;
    QPointF m_statePoint;
    QList<ChartAnimation*> m_animations;

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
