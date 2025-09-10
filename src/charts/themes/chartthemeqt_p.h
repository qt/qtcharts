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

#ifndef CHARTTHEMEQT_P_H
#define CHARTTHEMEQT_P_H

#include <private/charttheme_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartThemeQt : public ChartTheme
{
public:
    ChartThemeQt() : ChartTheme(QChart::ChartThemeQt)
    {
        // Series colors
        m_seriesColors << QRgb(0x80c342);
        m_seriesColors << QRgb(0x328930);
        m_seriesColors << QRgb(0x006325);
        m_seriesColors << QRgb(0x35322f);
        m_seriesColors << QRgb(0x5d5b59);
        m_seriesColors << QRgb(0x868482);
        m_seriesColors << QRgb(0xaeadac);
        m_seriesColors << QRgb(0xd7d6d5);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_labelBrush = QBrush(QRgb(0x35322f));
        m_axisLinePen = QPen(QRgb(0xd7d6d5));
        m_axisLinePen.setWidth(1);
        m_gridLinePen = QPen(QRgb(0xd7d6d5));
        m_gridLinePen.setWidth(1);
        m_minorGridLinePen = QPen(QRgb(0xd7d6d5));
        m_minorGridLinePen.setWidth(1);
        m_minorGridLinePen.setStyle(Qt::DashLine);
        m_backgroundShades = BackgroundShadesNone;
        m_outlinePen = QPen(QRgb(0x35322f));
        m_outlinePen.setWidthF(2.0);
    }
};

QT_END_NAMESPACE

#endif
