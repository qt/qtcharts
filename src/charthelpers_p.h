#ifndef CHARTHELPERS_P_H
#define CHARTHELPERS_P_H

#include <qnumeric.h>
#include <QPointF>

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
