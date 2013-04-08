/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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
#include "qchart.h" //because of QChart::ChartThemeId
#include <QRectF>
#include <QMargins>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class AxisItem;
class QAbstractSeries;
class ChartDataSet;
class AbstractDomain;
class ChartAxis;
class ChartAnimator;
class ChartBackground;
class ChartTitle;
class ChartAnimation;
class ChartLayout;

class ChartPresenter: public QObject
{
    Q_OBJECT
public:
    enum ZValues {
        BackgroundZValue = -1,
        ShadesZValue ,
        GridZValue,
        AxisZValue,
        SeriesZValue,
        LineChartZValue = SeriesZValue,
        SplineChartZValue = SeriesZValue,
        BarSeriesZValue = SeriesZValue,
        ScatterSeriesZValue = SeriesZValue,
        PieSeriesZValue = SeriesZValue,
        BoxPlotSeriesZValue = SeriesZValue,
        LegendZValue,
        TopMostZValue
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

    ChartPresenter(QChart *chart);
    virtual ~ChartPresenter();


    void setGeometry(QRectF rect);
    QRectF geometry() const;

    QGraphicsItem *rootItem(){ return m_chart; }
    ChartBackground *backgroundElement();
    ChartTitle *titleElement();
    QList<ChartAxis *> axisItems() const;
    QList<ChartItem *> chartItems() const;

    ChartItem* chartElement(QAbstractSeries* series) const;
    ChartAxis* chartElement(QAbstractAxis* axis) const;

    QLegend *legend();

    void setBackgroundBrush(const QBrush &brush);
    QBrush backgroundBrush() const;

    void setBackgroundPen(const QPen &pen);
    QPen backgroundPen() const;

    void setTitle(const QString &title);
    QString title() const;

    void setTitleFont(const QFont &font);
    QFont titleFont() const;

    void setTitleBrush(const QBrush &brush);
    QBrush titleBrush() const;

    void setBackgroundVisible(bool visible);
    bool isBackgroundVisible() const;

    void setBackgroundDropShadowEnabled(bool enabled);
    bool isBackgroundDropShadowEnabled() const;

    void setVisible(bool visible);

    void setAnimationOptions(QChart::AnimationOptions options);
    QChart::AnimationOptions animationOptions() const;

    void startAnimation(ChartAnimation *animation);

    void setState(State state,QPointF point);
    State state() const { return m_state; }
    QPointF statePoint() const { return m_statePoint; }
    ChartLayout *layout();

private:
    void createBackgroundItem();
    void createTitleItem();

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries *series);
    void handleSeriesRemoved(QAbstractSeries *series);
    void handleAxisAdded(QAbstractAxis *axis);
    void handleAxisRemoved(QAbstractAxis *axis);

private Q_SLOTS:
    void handleAnimationFinished();

Q_SIGNALS:
    void animationsFinished();

private:
    QChart *m_chart;
    QList<ChartItem *> m_chartItems;
    QList<ChartAxis *> m_axisItems;
    QList<QAbstractSeries *> m_series;
    QList<QAbstractAxis *> m_axes;
    QChart::AnimationOptions m_options;
    State m_state;
    QPointF m_statePoint;
    QList<ChartAnimation *> m_animations;
    ChartLayout *m_layout;
    ChartBackground *m_background;
    ChartTitle *m_title;
    QRectF m_rect;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H */
