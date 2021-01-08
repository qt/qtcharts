/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTTHEMEHIGHCONTRAST_P_H
#define CHARTTHEMEHIGHCONTRAST_P_H

#include <private/charttheme_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT ChartThemeHighContrast : public ChartTheme
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
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;
        m_backgroundDropShadowEnabled = true;

        // Axes and other
        m_labelBrush = QBrush(QRgb(0x181818));
        m_axisLinePen = QPen(QRgb(0x8c8c8c));
        m_axisLinePen.setWidth(2);
        m_gridLinePen = QPen(QRgb(0x8c8c8c));
        m_gridLinePen.setWidth(1);
        m_minorGridLinePen = QPen(QRgb(0x8c8c8c));
        m_minorGridLinePen.setWidth(1);
        m_minorGridLinePen.setStyle(Qt::DashLine);
        m_backgroundShadesBrush = QBrush(QRgb(0xffeecd));
        m_backgroundShades = BackgroundShadesHorizontal;
        m_outlinePen = QPen(QColor(Qt::black));
        m_outlinePen.setWidthF(2.0);
    }
};

QT_CHARTS_END_NAMESPACE

#endif
