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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTTHEMEHIGHCONTRAST_P_H
#define CHARTTHEMEHIGHCONTRAST_P_H

#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeHighContrast : public ChartTheme
{
public:
    ChartThemeHighContrast() : ChartTheme(QChart::ChartThemeHighContrast)
    {
        // Series colors
        m_seriesColors << QRgb(0x202020);
        m_seriesColors << QRgb(0x596a74);
        m_seriesColors << QRgb(0xffab03);
        m_seriesColors << QRgb(0x038e9b);
        m_seriesColors << QRgb(0xff4a41);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;
        m_backgroundDropShadowEnabled = true;

        // Axes and other
        m_titleBrush = QBrush(QRgb(0x181818));
        m_axisLinePen = QPen(QRgb(0x8c8c8c));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0x181818));
        m_gridLinePen = QPen(QRgb(0x8c8c8c));
        m_gridLinePen.setWidth(1);
        m_backgroundShadesBrush = QBrush(QRgb(0xffeecd));
        m_backgroundShades = BackgroundShadesHorizontal;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
