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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTTHEMEBLUECERULEAN_P_H
#define CHARTTHEMEBLUECERULEAN_P_H

#include <private/charttheme_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class ChartThemeBlueCerulean: public ChartTheme
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
        m_backgroundShades = BackgroundShadesNone;
        m_outlinePen = QPen(QRgb(0xebebeb));
        m_outlinePen.setWidthF(2.0);
    }
};

QT_CHARTS_END_NAMESPACE

#endif
