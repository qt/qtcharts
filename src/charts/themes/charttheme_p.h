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

#ifndef CHARTTHEME_H
#define CHARTTHEME_H

#include <private/chartthememanager_p.h>
#include <QtGui/QColor>
#include <QtGui/QGradientStops>

QT_CHARTS_BEGIN_NAMESPACE

class ChartTheme
{

public:
    enum BackgroundShadesMode {
        BackgroundShadesNone = 0,
        BackgroundShadesVertical,
        BackgroundShadesHorizontal,
        BackgroundShadesBoth
    };

protected:
    explicit ChartTheme(QChart::ChartTheme id = QChart::ChartThemeLight):m_id(id),
        m_backgroundShadesBrush(Qt::SolidPattern),
        m_backgroundShades(BackgroundShadesNone),
        m_backgroundDropShadowEnabled(false)
    {};
public:
    QChart::ChartTheme id() const { return m_id; }
    QList<QGradient> seriesGradients() const { return m_seriesGradients; }
    QList<QColor> seriesColors() const { return m_seriesColors; }
    QLinearGradient chartBackgroundGradient() const { return m_chartBackgroundGradient; }
    QFont masterFont() const { return m_masterFont; }
    QFont labelFont() const { return m_labelFont; }
    QBrush labelBrush() const { return m_labelBrush; }
    QPen axisLinePen() const { return m_axisLinePen; }
    QPen backgroundShadesPen() const { return m_backgroundShadesPen; }
    QPen outlinePen() const { return m_outlinePen; }
    QBrush backgroundShadesBrush() const { return m_backgroundShadesBrush; }
    BackgroundShadesMode backgroundShades() const { return m_backgroundShades; }
    bool isBackgroundDropShadowEnabled() const { return m_backgroundDropShadowEnabled; }
    QPen girdLinePen() const { return m_gridLinePen; }

protected:
    QChart::ChartTheme m_id;
    QList<QColor> m_seriesColors;
    QList<QGradient> m_seriesGradients;
    QLinearGradient m_chartBackgroundGradient;

    QFont m_masterFont;
    QFont m_labelFont;
    QBrush m_labelBrush;
    QPen m_axisLinePen;
    QPen m_backgroundShadesPen;
    QPen m_outlinePen;
    QBrush m_backgroundShadesBrush;
    BackgroundShadesMode m_backgroundShades;
    bool m_backgroundDropShadowEnabled;
    QPen m_gridLinePen;

};

QT_CHARTS_END_NAMESPACE

#endif // CHARTTHEME_H
