/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QCHART_H
#define QCHART_H

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGraphicsWidget>
#include <QtCore/QMargins>

class QGraphicsSceneResizeEvent;

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractSeries;
class QAbstractAxis;
class QLegend;
class QChartPrivate;
class QBoxPlotSeries;

class QT_CHARTS_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(QChart::ChartTheme theme READ theme WRITE setTheme)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible)
    Q_PROPERTY(bool dropShadowEnabled READ isDropShadowEnabled WRITE setDropShadowEnabled)
    Q_PROPERTY(qreal backgroundRoundness READ backgroundRoundness WRITE setBackgroundRoundness)
    Q_PROPERTY(QChart::AnimationOptions animationOptions READ animationOptions WRITE setAnimationOptions)
    Q_PROPERTY(QMargins margins READ margins WRITE setMargins)
    Q_PROPERTY(QChart::ChartType chartType READ chartType)
    Q_PROPERTY(bool plotAreaBackgroundVisible READ isPlotAreaBackgroundVisible WRITE setPlotAreaBackgroundVisible)
    Q_PROPERTY(bool localizeNumbers READ localizeNumbers WRITE setLocalizeNumbers)
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale)
    Q_PROPERTY(QRectF plotArea READ plotArea NOTIFY plotAreaChanged)
    Q_ENUMS(ChartTheme)
    Q_ENUMS(AnimationOption)
    Q_ENUMS(ChartType)

public:
    enum ChartType {
        ChartTypeUndefined = 0,
        ChartTypeCartesian,
        ChartTypePolar
    };

    enum ChartTheme {
        ChartThemeLight = 0,
        ChartThemeBlueCerulean,
        ChartThemeDark,
        ChartThemeBrownSand,
        ChartThemeBlueNcs,
        ChartThemeHighContrast,
        ChartThemeBlueIcy,
        ChartThemeQt
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

    void addAxis(QAbstractAxis *axis, Qt::Alignment alignment);
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
    void setBackgroundRoundness(qreal diameter);
    qreal backgroundRoundness() const;
    void setAnimationOptions(AnimationOptions options);
    AnimationOptions animationOptions() const;

    void zoomIn();
    void zoomOut();

    void zoomIn(const QRectF &rect);
    void zoom(qreal factor);
    void zoomReset();
    bool isZoomed();

    void scroll(qreal dx, qreal dy);

    QLegend *legend() const;

    void setMargins(const QMargins &margins);
    QMargins margins() const;

    QRectF plotArea() const;
    void setPlotAreaBackgroundBrush(const QBrush &brush);
    QBrush plotAreaBackgroundBrush() const;
    void setPlotAreaBackgroundPen(const QPen &pen);
    QPen plotAreaBackgroundPen() const;
    void setPlotAreaBackgroundVisible(bool visible = true);
    bool isPlotAreaBackgroundVisible() const;
    void setLocalizeNumbers(bool localize);
    bool localizeNumbers() const;
    void setLocale(const QLocale &locale);
    QLocale locale() const;

    QPointF mapToValue(const QPointF &position, QAbstractSeries *series = 0);
    QPointF mapToPosition(const QPointF &value, QAbstractSeries *series = 0);

    ChartType chartType() const;

signals:
    void plotAreaChanged(const QRectF &plotArea);

protected:
    explicit QChart(QChart::ChartType type, QGraphicsItem *parent, Qt::WindowFlags wFlags);
    QScopedPointer<QChartPrivate> d_ptr;
    friend class QLegend;
    friend class DeclarativeChart;
    friend class ChartDataSet;
    friend class ChartPresenter;
    friend class ChartThemeManager;
    friend class QAbstractSeries;
    friend class QBoxPlotSeriesPrivate;

private:
    Q_DISABLE_COPY(QChart)
};

QT_CHARTS_END_NAMESPACE

Q_DECLARE_OPERATORS_FOR_FLAGS(QT_CHARTS_NAMESPACE::QChart::AnimationOptions)

#endif // QCHART_H
