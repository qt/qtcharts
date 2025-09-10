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

#ifndef CANDLESTICKDATA_P_H
#define CANDLESTICKDATA_P_H

#include <QtCharts/QCandlestickSeries>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT CandlestickData
{
public:
    CandlestickData() :
        m_timestamp(0.0),
        m_open(0.0),
        m_high(0.0),
        m_low(0.0),
        m_close(0.0),
        m_index(0),
        m_maxX(0.0),
        m_minX(0.0),
        m_maxY(0.0),
        m_minY(0.0),
        m_series(nullptr),
        m_seriesIndex(0),
        m_seriesCount(0)
    {
    }

    // Candlestick related statistics
    qreal m_timestamp;
    qreal m_open;
    qreal m_high;
    qreal m_low;
    qreal m_close;
    int m_index;

    // Domain boundaries
    qreal m_maxX;
    qreal m_minX;
    qreal m_maxY;
    qreal m_minY;

    // Series related data
    QCandlestickSeries *m_series;
    int m_seriesIndex;
    int m_seriesCount;
};

QT_END_NAMESPACE

#endif // CANDLESTICKDATA_P_H
