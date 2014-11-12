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

#ifndef CHARTHELPERS_P_H
#define CHARTHELPERS_P_H

#include <QtCore/QtNumeric>
#include <QtCore/QPointF>

static inline bool isValidValue(qreal value)
{
    if (qIsNaN(value) || qIsInf(value)) {
        qWarning("Ignored NaN, Inf, or -Inf value.");
        return false;
    }
    return true;
}

static inline bool isValidValue(qreal x, qreal y)
{
    return (isValidValue(x) && isValidValue(y));
}

static inline bool isValidValue(const QPointF point)
{
    return (isValidValue(point.x()) && isValidValue(point.y()));
}

#endif // CHARTHELPERS_P_H
