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

#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeBlueNcs: public ChartTheme
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
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_titleBrush = QBrush(QRgb(0x404044));
        m_axisLinePen = QPen(QRgb(0xd6d6d6));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0x404044));
        m_gridLinePen = QPen(QRgb(0xe2e2e2));
        m_gridLinePen.setWidth(1);
        m_backgroundShades = BackgroundShadesNone;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
