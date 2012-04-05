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

#ifndef QCHART_H
#define QCHART_H

#include <QSeries>
#include <QLegend>
#include <QGraphicsWidget>

class QGraphicsSceneResizeEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSeries;
class QChartAxis;
class QLegend;
struct QChartPrivate;

class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
    Q_ENUMS(ChartTheme)

public:
    enum ChartTheme {
        ChartThemeLight = 0,
        ChartThemeBlueCerulean,
        ChartThemeDark,
        ChartThemeBrownSand,
        ChartThemeBlueNcs,
        ChartThemeHighContrast,
        ChartThemeBlueIcy
    };

    enum AnimationOption {
        NoAnimation = 0x0,
        GridAxisAnimations = 0x1,
        SeriesAnimations =0x2,
        AllAnimations = 0x3
    };

    Q_DECLARE_FLAGS(AnimationOptions, AnimationOption)

public:
    explicit QChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~QChart();

    void addSeries(QSeries *series, QChartAxis *axisY = 0);
    void removeSeries(QSeries *series);
    void removeAllSeries();

    void setTheme(QChart::ChartTheme theme);
    QChart::ChartTheme theme() const;

    void setTitle(const QString& title);
    QString title() const;
    void setTitleFont(const QFont& font);
    QFont titleFont() const;
    void setTitleBrush(const QBrush &brush);
    QBrush titleBrush() const;

    void setBackgroundBrush(const QBrush &brush);
    QBrush backgroundBrush() const;
    void setBackgroundPen(const QPen &pen);
    QPen backgroundPen() const;

    void setBackgroundVisible(bool visible);
    bool isBackgroundVisible() const;

    void setAnimationOptions(AnimationOptions options);
    AnimationOptions animationOptions() const;

    void zoomIn();
    void zoomIn(const QRectF &rect);
    void zoomOut();
    void scrollLeft();
    void scrollRight();
    void scrollUp();
    void scrollDown();

    QChartAxis* axisX() const;
    QChartAxis* axisY(QSeries* series = 0) const;

    QLegend* legend() const;
    QRectF margins() const;

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

protected:
    QScopedPointer<QChartPrivate> d_ptr;
    friend class QLegend;
    friend class ChartPresenter;
    Q_DISABLE_COPY(QChart)
};

QTCOMMERCIALCHART_END_NAMESPACE

Q_DECLARE_OPERATORS_FOR_FLAGS(QTCOMMERCIALCHART_NAMESPACE::QChart::AnimationOptions)

#endif
