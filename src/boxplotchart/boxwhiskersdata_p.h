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

#ifndef BOXWHISKERSDATA_P_H
#define BOXWHISKERSDATA_P_H

#include "qchartglobal.h"
#include <QSizeF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class BoxWhiskersData
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

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BOXWHISKERSDATA_P_H
