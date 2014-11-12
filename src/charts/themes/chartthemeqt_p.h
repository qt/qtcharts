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

#ifndef CHARTTHEMEQT_P_H
#define CHARTTHEMEQT_P_H

#include <private/charttheme_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class ChartThemeQt : public ChartTheme
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
        m_backgroundShades = BackgroundShadesNone;
        m_outlinePen = QPen(QRgb(0x35322f));
        m_outlinePen.setWidthF(2.0);
    }
};

QT_CHARTS_END_NAMESPACE

#endif
