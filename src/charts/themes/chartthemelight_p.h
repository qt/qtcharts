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

#ifndef CHARTTHEMELIGHT_P_H
#define CHARTTHEMELIGHT_P_H

#include <private/charttheme_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartThemeLight: public ChartTheme
{
public:
    ChartThemeLight() : ChartTheme(QChart::ChartThemeLight)
    {
        // Series colors
        m_seriesColors << QRgb(0x209fdf);
        m_seriesColors << QRgb(0x99ca53);
        m_seriesColors << QRgb(0xf6a625);
        m_seriesColors << QRgb(0x6d5fd5);
        m_seriesColors << QRgb(0xbf593e);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;
        // There is a performance issue in the drop shadow implementation, so disabled for now
//        m_backgroundDropShadowEnabled = true;

        // Axes and other
        m_axisLinePen = QPen(0xd6d6d6);
        m_axisLinePen.setWidth(1);
        m_labelBrush = QBrush(QRgb(0x404044));
        m_gridLinePen = QPen(QRgb(0xe2e2e2));
        m_gridLinePen.setWidth(1);
        m_minorGridLinePen = QPen(QRgb(0xe2e2e2));
        m_minorGridLinePen.setWidth(1);
        m_minorGridLinePen.setStyle(Qt::DashLine);
        m_backgroundShades = BackgroundShadesNone;
        m_outlinePen = QPen(0x4d4d4d);
        m_outlinePen.setWidthF(2.0);
    }
};

QT_END_NAMESPACE

#endif
