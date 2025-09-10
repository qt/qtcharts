// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTTHEMEMANAGER_H
#define CHARTTHEMEMANAGER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtGui/QColor>
#include <QtGui/QGradientStops>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/qmap.h>

QT_BEGIN_NAMESPACE
class ChartTheme;

class Q_CHARTS_EXPORT ChartThemeManager: public QObject
{
    Q_OBJECT
public:
    enum BackgroundShadesMode {
        BackgroundShadesNone = 0,
        BackgroundShadesVertical,
        BackgroundShadesHorizontal,
        BackgroundShadesBoth
    };

public:
    explicit ChartThemeManager(QChart* chart);
    void setTheme(QChart::ChartTheme theme);
    ChartTheme* theme() const { return m_theme.data(); }
    void decorateChart(QChart *chart, ChartTheme* theme) const;
    void decorateLegend(QLegend *legend, ChartTheme* theme) const;
    void updateSeries(QAbstractSeries *series);
    QMap<QAbstractSeries *, int> seriesMap() const { return m_seriesMap; }

public:
    static QList<QGradient> generateSeriesGradients(const QList<QColor>& colors);
    static QColor colorAt(const QColor &start, const QColor &end, qreal pos);
    static QColor colorAt(const QGradient &gradient, qreal pos);

private:
    int createIndexKey(const QList<int> &keys) const;
    int seriesCount(QAbstractSeries::SeriesType type) const;

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries *series);
    void handleSeriesRemoved(QAbstractSeries *series);
    void handleAxisAdded(QAbstractAxis *axis);
    void handleAxisRemoved(QAbstractAxis *axis);

protected:
    QScopedPointer<ChartTheme> m_theme;
    QMap<QAbstractSeries *,int> m_seriesMap;
    QList<QAbstractAxis *> m_axisList;
    QChart* m_chart;
};

QT_END_NAMESPACE

#endif // CHARTTHEME_H
