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

#ifndef CHARTCONFIG_H
#define CHARTCONFIG_H

#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE

class ChartConfig
{
private:
    ChartConfig() {
        m_instance = this;
    }
public:
    static ChartConfig *instance() {
        if (!m_instance) {
            m_instance = new ChartConfig();
        }
        return m_instance;
    }

private:
    static ChartConfig *m_instance;
};


ChartConfig *ChartConfig::m_instance = 0;

QT_CHARTS_END_NAMESPACE

#endif
