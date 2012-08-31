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
#include <QMargins>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartElement;
class QAbstractSeries;
class ChartDataSet;
class Domain;
class ChartAxis;
class ChartTheme;
class ChartAnimator;
class ChartBackground;
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

    ChartPresenter(QChart* chart,ChartDataSet *dataset);
    virtual ~ChartPresenter();

    ChartTheme *chartTheme() const { return m_chartTheme; }
    ChartDataSet *dataSet() const { return m_dataset; }
    QGraphicsItem* rootItem() const { return m_chart; }
    QGraphicsRectItem* backgroundItem();
    QGraphicsItem* titleItem();
    QList<ChartAxis*> axisItems() const;

    QLegend* legend();

    void setBackgroundBrush(const QBrush& brush);
    QBrush backgroundBrush() const;

    void setBackgroundPen(const QPen& pen);
    QPen backgroundPen() const;

    void setTitle(const QString& title);
    QString title() const;

    void setTitleFont(const QFont& font);
    QFont titleFont() const;

    void setTitleBrush(const QBrush &brush);
    QBrush titleBrush() const;

    void setBackgroundVisible(bool visible);
    bool isBackgroundVisible() const;

    void setBackgroundDropShadowEnabled(bool enabled);
    bool isBackgroundDropShadowEnabled() const;

    void setVisible(bool visible);

    void setTheme(QChart::ChartTheme theme,bool force = true);
    QChart::ChartTheme theme();

    void setAnimationOptions(QChart::AnimationOptions options);
    QChart::AnimationOptions animationOptions() const;

    void zoomIn(qreal factor);
    void zoomIn(const QRectF& rect);
    void zoomOut(qreal factor);
    void scroll(qreal dx,qreal dy);

    void setGeometry(const QRectF& rect);
    QRectF geometry() { return m_rect; }

    void startAnimation(ChartAnimation* animation);
    State state() const { return m_state; }
    QPointF statePoint() const { return m_statePoint; }

    void resetAllElements();

    void setMinimumMargins(const QMargins& margins);
    QMargins minimumMargins() const;
    QGraphicsLayout* layout();

private:
    void createBackgroundItem();
    void createTitleItem();
    void selectVisibleAxis();

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries* series,Domain* domain);
    void handleSeriesRemoved(QAbstractSeries* series);
    void handleAxisAdded(QAbstractAxis* axis,Domain* domain);
    void handleAxisRemoved(QAbstractAxis* axis);
    void handleAxisVisibleChanged(bool visible);

private Q_SLOTS:
    void handleAnimationFinished();

Q_SIGNALS:
    void geometryChanged(const QRectF& rect);
    void animationsFinished();
    void marginsChanged(QRectF margins);

private:
    QChart* m_chart;
    ChartDataSet* m_dataset;
    ChartTheme *m_chartTheme;
    QMap<QAbstractSeries*, ChartElement*> m_chartItems;
    QMap<QAbstractAxis*, ChartAxis*> m_axisItems;
    QRectF m_rect;
    QChart::AnimationOptions m_options;
    State m_state;
    QPointF m_statePoint;
    QList<ChartAnimation*> m_animations;
    ChartLayout* m_layout;
    ChartBackground* m_backgroundItem;
    QGraphicsSimpleTextItem* m_titleItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTPRESENTER_H */
