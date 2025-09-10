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

#ifndef BOXWHISKERSDATA_P_H
#define BOXWHISKERSDATA_P_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QSizeF>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT BoxWhiskersData
{
public:
    BoxWhiskersData() :
        m_lowerExtreme(0.0),
        m_lowerQuartile(0.0),
        m_median(0.0),
        m_upperQuartile(0.0),
        m_upperExtreme(0.0),
        m_index(0),
        m_boxItems(0),
        m_maxX(0.0),
        m_minX(0.0),
        m_maxY(0.0),
        m_minY(0.0),
        m_seriesIndex(0),
        m_seriesCount(0)
    {
    }

    // Box related statistics
    qreal m_lowerExtreme;
    qreal m_lowerQuartile;
    qreal m_median;
    qreal m_upperQuartile;
    qreal m_upperExtreme;
    int   m_index;
    int   m_boxItems;

    // Domain boundaries, axis
    qreal m_maxX;
    qreal m_minX;
    qreal m_maxY;
    qreal m_minY;

    // Serieses related data
    int m_seriesIndex;
    int m_seriesCount;
};

QT_END_NAMESPACE

#endif // BOXWHISKERSDATA_P_H
