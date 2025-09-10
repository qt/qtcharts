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

#ifndef CHARTTHEMEBLUENCS_P_H
#define CHARTTHEMEBLUENCS_P_H

#include <private/charttheme_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartThemeBlueNcs: public ChartTheme
{
public:
    ChartThemeBlueNcs() : ChartTheme(QChart::ChartThemeBlueNcs)
    {
        // Series colors
        m_seriesColors << QRgb(0x1db0da);
        m_seriesColors << QRgb(0x1341a6);
        m_seriesColors << QRgb(0x88d41e);
        m_seriesColors << QRgb(0xff8e1a);
        m_seriesColors << QRgb(0x398ca3);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_labelBrush = QBrush(QRgb(0x404044));
        m_axisLinePen = QPen(QRgb(0xd6d6d6));
        m_axisLinePen.setWidth(2);
        m_gridLinePen = QPen(QRgb(0xe2e2e2));
        m_gridLinePen.setWidth(1);
        m_minorGridLinePen = QPen(QRgb(0xe2e2e2));
        m_minorGridLinePen.setWidth(1);
        m_minorGridLinePen.setStyle(Qt::DashLine);
        m_backgroundShades = BackgroundShadesNone;
        m_outlinePen = QPen(QRgb(0x474747));
        m_outlinePen.setWidthF(2.0);
    }
};

QT_END_NAMESPACE

#endif
