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

#ifndef CHARTTHEMEBLUECERULEAN_P_H
#define CHARTTHEMEBLUECERULEAN_P_H

#include <private/charttheme_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartThemeBlueCerulean: public ChartTheme
{
public:
    ChartThemeBlueCerulean() : ChartTheme(QChart::ChartThemeBlueCerulean) {
        // Series colors
        m_seriesColors << QRgb(0xc7e85b);
        m_seriesColors << QRgb(0x1cb54f);
        m_seriesColors << QRgb(0x5cbf9b);
        m_seriesColors << QRgb(0x009fbf);
        m_seriesColors << QRgb(0xee7392);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
        backgroundGradient.setColorAt(0.0, QRgb(0x056189));
        backgroundGradient.setColorAt(1.0, QRgb(0x101a31));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_labelBrush = QBrush(QRgb(0xffffff));
        m_axisLinePen = QPen(QRgb(0xd6d6d6));
        m_axisLinePen.setWidth(2);
        m_gridLinePen = QPen(QRgb(0x84a2b0));
        m_gridLinePen.setWidth(1);
        m_minorGridLinePen = QPen(QRgb(0x84a2b0));
        m_minorGridLinePen.setWidth(1);
        m_minorGridLinePen.setStyle(Qt::DashLine);
        m_backgroundShades = BackgroundShadesNone;
        m_outlinePen = QPen(QRgb(0xebebeb));
        m_outlinePen.setWidthF(2.0);
    }
};

QT_END_NAMESPACE

#endif
