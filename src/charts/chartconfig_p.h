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

#ifndef CHARTCONFIG_H
#define CHARTCONFIG_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartConfig
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

QT_END_NAMESPACE

#endif
