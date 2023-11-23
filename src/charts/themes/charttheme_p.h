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

#ifndef CHARTTHEME_H
#define CHARTTHEME_H

#include <private/chartthememanager_p.h>
#include <QtGui/QColor>
#include <QtGui/QGradientStops>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartTheme
{

public:
    enum BackgroundShadesMode {
        BackgroundShadesNone = 0,
        BackgroundShadesVertical,
        BackgroundShadesHorizontal,
        BackgroundShadesBoth
    };

protected:
    explicit ChartTheme(QChart::ChartTheme id = QChart::ChartThemeLight):m_id(id),
        m_backgroundShadesBrush(Qt::SolidPattern),
        m_backgroundShades(BackgroundShadesNone),
        m_backgroundDropShadowEnabled(false)
    {};
public:
    QChart::ChartTheme id() const { return m_id; }
    QList<QGradient> seriesGradients() const { return m_seriesGradients; }
    QList<QColor> seriesColors() const { return m_seriesColors; }
    QLinearGradient chartBackgroundGradient() const { return m_chartBackgroundGradient; }
    QFont masterFont() const { return m_masterFont; }
    QFont labelFont() const { return m_labelFont; }
    QBrush labelBrush() const { return m_labelBrush; }
    QPen axisLinePen() const { return m_axisLinePen; }
    QPen backgroundShadesPen() const { return m_backgroundShadesPen; }
    QPen outlinePen() const { return m_outlinePen; }
    QBrush backgroundShadesBrush() const { return m_backgroundShadesBrush; }
    BackgroundShadesMode backgroundShades() const { return m_backgroundShades; }
    bool isBackgroundDropShadowEnabled() const { return m_backgroundDropShadowEnabled; }
    QPen gridLinePen() const { return m_gridLinePen; }
    QPen minorGridLinePen() const { return m_minorGridLinePen; }

protected:
    QChart::ChartTheme m_id;
    QList<QColor> m_seriesColors;
    QList<QGradient> m_seriesGradients;
    QLinearGradient m_chartBackgroundGradient;

    QFont m_masterFont;
    QFont m_labelFont;
    QBrush m_labelBrush;
    QPen m_axisLinePen;
    QPen m_backgroundShadesPen;
    QPen m_outlinePen;
    QBrush m_backgroundShadesBrush;
    BackgroundShadesMode m_backgroundShades;
    bool m_backgroundDropShadowEnabled;
    QPen m_gridLinePen;
    QPen m_minorGridLinePen;

};

QT_END_NAMESPACE

#endif // CHARTTHEME_H
