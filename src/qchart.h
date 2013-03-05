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

#ifndef QCHART_H
#define QCHART_H

#include <QAbstractSeries>
#include <QLegend>
#include <QGraphicsWidget>
#include <QMargins>

class QGraphicsSceneResizeEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAbstractSeries;
class QAbstractAxis;
class QLegend;
class QChartPrivate;

class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(QChart::ChartTheme theme READ theme WRITE setTheme)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible)
    Q_PROPERTY(bool dropShadowEnabled READ isDropShadowEnabled WRITE setDropShadowEnabled)
    Q_PROPERTY(QChart::AnimationOptions animationOptions READ animationOptions WRITE setAnimationOptions)
    Q_PROPERTY(QMargins minimumMargins READ minimumMargins WRITE setMinimumMargins)
    Q_PROPERTY(QMargins margins READ margins WRITE setMargins)
    Q_ENUMS(ChartTheme)
    Q_ENUMS(AnimationOption)

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
        SeriesAnimations = 0x2,
        AllAnimations = 0x3
    };

    Q_DECLARE_FLAGS(AnimationOptions, AnimationOption)

public:
    explicit QChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~QChart();

    void addSeries(QAbstractSeries *series);
    void removeSeries(QAbstractSeries *series);
    void removeAllSeries();
    QList<QAbstractSeries *> series() const;

    // *** deprecated ***
    void setAxisX(QAbstractAxis *axis, QAbstractSeries *series = 0);
    void setAxisY(QAbstractAxis *axis, QAbstractSeries *series = 0);
    QAbstractAxis *axisX(QAbstractSeries *series = 0) const;
    QAbstractAxis *axisY(QAbstractSeries *series = 0) const;
    // ******************

    void addAxis(QAbstractAxis *axis,Qt::Alignment alignment);
    void removeAxis(QAbstractAxis *axis);
    QList<QAbstractAxis*> axes(Qt::Orientations orientation = Qt::Horizontal|Qt::Vertical, QAbstractSeries *series = 0) const;

    void createDefaultAxes();

    void setTheme(QChart::ChartTheme theme);
    QChart::ChartTheme theme() const;

    void setTitle(const QString &title);
    QString title() const;
    void setTitleFont(const QFont &font);
    QFont titleFont() const;
    void setTitleBrush(const QBrush &brush);
    QBrush titleBrush() const;

    void setBackgroundBrush(const QBrush &brush);
    QBrush backgroundBrush() const;
    void setBackgroundPen(const QPen &pen);
    QPen backgroundPen() const;
    void setBackgroundVisible(bool visible = true);
    bool isBackgroundVisible() const;

    void setDropShadowEnabled(bool enabled = true);
    bool isDropShadowEnabled() const;
    void setAnimationOptions(AnimationOptions options);
    AnimationOptions animationOptions() const;

    void zoomIn();
    void zoomOut();

    void zoomIn(const QRectF &rect);
    void zoom(qreal factor);

    void scroll(qreal dx, qreal dy);

    QLegend *legend() const;

    void setMinimumMargins(const QMargins& margins);
    QMargins minimumMargins() const;

    void setMargins(const QMargins &margins);
    QMargins margins() const;

    QRectF plotArea() const;

    QPointF mapToValue(const QPointF &position, QAbstractSeries *series = 0);
    QPointF mapToPosition(const QPointF &value, QAbstractSeries *series = 0);

protected:
    QScopedPointer<QChartPrivate> d_ptr;
    friend class QLegend;
    friend class DeclarativeChart;
    friend class ChartDataSet;
    friend class ChartPresenter;
    friend class ChartThemeManager;
    friend class QAbstractSeries;
    Q_DISABLE_COPY(QChart)
};

QTCOMMERCIALCHART_END_NAMESPACE

Q_DECLARE_OPERATORS_FOR_FLAGS(QTCOMMERCIALCHART_NAMESPACE::QChart::AnimationOptions)

#endif // QCHART_H
