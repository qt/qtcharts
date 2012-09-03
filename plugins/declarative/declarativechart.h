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

#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtCore/QtGlobal>
#include <QDeclarativeItem>
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeMargins;

class DeclarativeChart : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme)
    Q_PROPERTY(Animation animationOptions READ animationOptions WRITE setAnimationOptions)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
    Q_PROPERTY(QLegend *legend READ legend)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool dropShadowEnabled READ dropShadowEnabled WRITE setDropShadowEnabled NOTIFY dropShadowEnabledChanged)
    Q_PROPERTY(qreal topMargin READ topMargin)
    Q_PROPERTY(qreal bottomMargin READ bottomMargin)
    Q_PROPERTY(qreal leftMargin READ leftMargin)
    Q_PROPERTY(qreal rightMargin READ rightMargin)
    Q_PROPERTY(DeclarativeMargins *minimumMargins READ minimumMargins NOTIFY minimumMarginsChanged REVISION 1)
    Q_PROPERTY(QRectF plotArea READ plotArea NOTIFY plotAreaChanged REVISION 1)
    Q_ENUMS(Animation)
    Q_ENUMS(Theme)
    Q_ENUMS(SeriesType)

public:
    // duplicating enums from QChart to make the QML api namings 1-to-1 with the C++ api
    enum Theme {
        ChartThemeLight = 0,
        ChartThemeBlueCerulean,
        ChartThemeDark,
        ChartThemeBrownSand,
        ChartThemeBlueNcs,
        ChartThemeHighContrast,
        ChartThemeBlueIcy
    };

    enum Animation {
        NoAnimation = 0x0,
        GridAxisAnimations = 0x1,
        SeriesAnimations =0x2,
        AllAnimations = 0x3
    };

    enum SeriesType {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline,
        SeriesTypeHorizontalBar,
        SeriesTypeHorizontalStackedBar,
        SeriesTypeHorizontalPercentBar
    };

public:
    DeclarativeChart(QDeclarativeItem *parent = 0);
    ~DeclarativeChart();

public: // From QDeclarativeItem/QGraphicsItem
    void childEvent(QChildEvent *event);
    void componentComplete();
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

public:
    void setTheme(DeclarativeChart::Theme theme);
    DeclarativeChart::Theme theme();
    void setAnimationOptions(DeclarativeChart::Animation animations);
    DeclarativeChart::Animation animationOptions();
    void setTitle(QString title);
    QString title();
    QLegend *legend();
    QFont titleFont() const;
    void setTitleFont(const QFont& font);
    void setTitleColor(QColor color);
    QColor titleColor();
    void setBackgroundColor(QColor color);
    QColor backgroundColor();
    int count();
    void setDropShadowEnabled(bool enabled);
    bool dropShadowEnabled();
    qreal topMargin();
    qreal bottomMargin();
    qreal leftMargin();
    qreal rightMargin();
    void createDefaultAxes(QAbstractSeries* series);
    DeclarativeMargins *minimumMargins() { return m_minMargins; }
    QRectF plotArea() { return m_chart->plotArea(); }

public:
    Q_INVOKABLE QAbstractSeries *series(int index);
    Q_INVOKABLE QAbstractSeries *series(QString seriesName);
    Q_INVOKABLE QAbstractSeries *createSeries(DeclarativeChart::SeriesType type, QString name = "");
    Q_INVOKABLE void setAxisX(QAbstractAxis *axis, QAbstractSeries *series = 0);
    Q_INVOKABLE void setAxisY(QAbstractAxis *axis, QAbstractSeries *series = 0);
    Q_INVOKABLE void createDefaultAxes();
    Q_INVOKABLE QAbstractAxis *axisX(QAbstractSeries *series = 0);
    Q_INVOKABLE QAbstractAxis *axisY(QAbstractSeries *series = 0);

    Q_INVOKABLE void zoom(qreal factor);
    Q_INVOKABLE void scrollLeft(qreal pixels);
    Q_INVOKABLE void scrollRight(qreal pixels);
    Q_INVOKABLE void scrollUp(qreal pixels);
    Q_INVOKABLE void scrollDown(qreal pixels);

Q_SIGNALS:
    void axisLabelsChanged();
    void titleColorChanged(QColor color);
    void backgroundColorChanged();
    void dropShadowEnabledChanged(bool enabled);
    void minimumMarginsChanged();
    void plotAreaChanged(QRectF plotArea);

public Q_SLOTS:
    void changeMinimumMargins(int top, int bottom, int left, int right);
    void handleAxisXSet(QAbstractAxis *axis);
    void handleAxisYSet(QAbstractAxis *axis);

private:
    // Extending QChart with DeclarativeChart is not possible because QObject does not support
    // multi inheritance, so we now have a QChart as a member instead
    QChart *m_chart;
    //QMargins m_chartMargins;
    DeclarativeMargins *m_minMargins;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVECHART_H
