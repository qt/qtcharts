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

#ifndef CHARTTHEMESYSTEM_P_H
#define CHARTTHEMESYSTEM_P_H

#include <private/charttheme_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#ifdef Q_OS_WIN
#include <windows.h>
#include <stdio.h>
#endif

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartThemeSystem: public ChartTheme
{
public:
    // System theme not used at the moment (the user is not able to select this theme)
    ChartThemeSystem() : ChartTheme(QChart::ChartThemeLight /*QChart::ChartThemeSystem*/)
    {
#if defined(Q_OS_WIN)
        // We could also use theme specific window frame color as a series base color (it would give more
        // variation to the base colors in addition to the blue and black used now)

        // First series base color from COLOR_HIGHLIGHT
        DWORD colorHighlight;
        colorHighlight = GetSysColor(COLOR_HIGHLIGHT);
        m_seriesColors.append(QColor(GetRValue(colorHighlight),
                                     GetGValue(colorHighlight),
                                     GetBValue(colorHighlight)));

        // Second series base color from COLOR_WINDOWFRAME
        DWORD colorWindowFrame;
        colorWindowFrame = GetSysColor(COLOR_WINDOWFRAME);
        m_seriesColors.append(QColor(GetRValue(colorWindowFrame),
                                     GetGValue(colorWindowFrame),
                                     GetBValue(colorWindowFrame)));

        // Third series base color from the middle of the COLOR_ACTIVECAPTION /
        // COLOR_GRADIENTACTIVECAPTION gradient
        DWORD colorGradientActiveCaptionLeft;
        colorGradientActiveCaptionLeft = GetSysColor(COLOR_ACTIVECAPTION);
        DWORD colorGradientActiveCaptionRight;
        colorGradientActiveCaptionRight = GetSysColor(COLOR_GRADIENTACTIVECAPTION);
        QLinearGradient g;
        QColor start = QColor(GetRValue(colorGradientActiveCaptionLeft),
                              GetGValue(colorGradientActiveCaptionLeft),
                              GetBValue(colorGradientActiveCaptionLeft));
        g.setColorAt(0.0, start);
        QColor end = QColor(GetRValue(colorGradientActiveCaptionRight),
                            GetGValue(colorGradientActiveCaptionRight),
                            GetBValue(colorGradientActiveCaptionRight));
        g.setColorAt(1.0, end);
        m_seriesColors.append(ChartThemeManager::colorAt(g, 0.5));

        // Generate gradients from the base colors
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background fill color from COLOR_WINDOW
        QLinearGradient backgroundGradient;
        DWORD colorWindow;
        colorWindow = GetSysColor(COLOR_WINDOW);
        backgroundGradient.setColorAt(0.0, QColor(GetRValue(colorWindow),
                                      GetGValue(colorWindow),
                                      GetBValue(colorWindow)));
        backgroundGradient.setColorAt(1.0, QColor(GetRValue(colorWindow),
                                      GetGValue(colorWindow),
                                      GetBValue(colorWindow)));
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

#elif defined(Q_OS_LINUX)
        // Using a hard coded theme for Linux system theme
        m_seriesColors << QRgb(0x60a6e6);
        m_seriesColors << QRgb(0x92ca66);
        m_seriesColors << QRgb(0xeba85f);
        m_seriesColors << QRgb(0xfc5751);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_axisLinePen = QPen(0xd6d6d6);
        m_axisLinePen.setWidth(1);
        m_labelBrush = QBrush(QRgb(0x404044));
        m_gridLinePen = QPen(QRgb(0xe2e2e2));
        m_gridLinePen.setWidth(1);
        m_minorGridLinePen = QPen(QRgb(0x404044));
        m_minorGridLinePen.setWidth(1);
        m_minorGridLinePen.setStyle(Qt::DashLine);
        m_backgroundShades = BackgroundShadesNone;

#elif defined(Q_OS_MAC)
        // Using a hard coded theme for OSX system theme; the colors match the OSX 10.7 colors
        m_seriesColors << QRgb(0x60a6e6);
        m_seriesColors << QRgb(0x92ca66);
        m_seriesColors << QRgb(0xeba85f);
        m_seriesColors << QRgb(0xfc5751);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

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

#else
        // Hard coded theme
        m_seriesColors << QRgb(0x60a6e6);
        m_seriesColors << QRgb(0x92ca66);
        m_seriesColors << QRgb(0xeba85f);
        m_seriesColors << QRgb(0xfc5751);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

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
#endif
    }
};

QT_END_NAMESPACE

#endif // CHARTTHEMESYSTEM_P_H
