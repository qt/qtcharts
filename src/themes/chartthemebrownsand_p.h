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

#ifndef CHARTTHEMEBROWNSAND_P_H
#define CHARTTHEMEBROWNSAND_P_H

#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeBrownSand: public ChartTheme
{
public:
    ChartThemeBrownSand() : ChartTheme(QChart::ChartThemeBrownSand)
    {
        // Series colors
        m_seriesColors << QRgb(0xb39b72);
        m_seriesColors << QRgb(0xb3b376);
        m_seriesColors << QRgb(0xc35660);
        m_seriesColors << QRgb(0x536780);
        m_seriesColors << QRgb(0x494345);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xf3ece0));
        backgroundGradient.setColorAt(1.0, QRgb(0xf3ece0));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_titleBrush = QBrush(QRgb(0x404044));
        m_axisLinePen = QPen(QRgb(0xb5b0a7));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0x404044));
        m_gridLinePen = QPen(QRgb(0xd4cec3));
        m_gridLinePen.setWidth(1);
        m_backgroundShades = BackgroundShadesNone;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
