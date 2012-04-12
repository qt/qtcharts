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

#ifndef PIESLICEDATA_P_H
#define PIESLICEDATA_P_H

#include "qchartglobal.h"
#include "qpieslice.h"
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

template <class T>
class Themed : public T
{
public:
    Themed():m_isThemed(true) {}

    inline T &operator=(const T &other) { return T::operator =(other); }

    inline bool operator!=(const T &other) const { return T::operator !=(other); }
    inline bool operator!=(const Themed &other) const
    {
        if (T::operator !=(other))
            return true;

        if (m_isThemed != other.m_isThemed)
            return true;

        return false;
    }

    inline void setThemed(bool state) { m_isThemed = state; }
    inline bool isThemed() const { return m_isThemed; }

private:
    bool m_isThemed;
};

class PieSliceData
{
public:
    PieSliceData()
    {
        m_value = 0;

        m_isExploded = false;
        m_explodeDistanceFactor = 0.15;

        m_isLabelVisible = false;
        m_labelArmLengthFactor = 0.15;

        m_percentage = 0;
        m_radius = 0;
        m_startAngle = 0;
        m_angleSpan = 0;
    }

    bool operator!=(const PieSliceData &other) const
    {
        if (!qFuzzyIsNull(m_value - other.m_value))
            return true;

        if (m_slicePen != other.m_slicePen ||
            m_sliceBrush != other.m_sliceBrush)
            return true;

        if (m_isExploded != other.m_isExploded ||
            !qFuzzyIsNull(m_explodeDistanceFactor - other.m_explodeDistanceFactor))
            return true;

        if (m_isLabelVisible != other.m_isLabelVisible ||
            m_labelText != other.m_labelText ||
            m_labelFont != other.m_labelFont ||
            !qFuzzyIsNull(m_labelArmLengthFactor - other.m_labelArmLengthFactor) ||
            m_labelPen != other.m_labelPen)
            return true;

        if (!qFuzzyIsNull(m_percentage - other.m_percentage) ||
            m_center != other.m_center ||
            !qFuzzyIsNull(m_radius - other.m_radius) ||
            !qFuzzyIsNull(m_startAngle - other.m_startAngle) ||
            !qFuzzyIsNull(m_angleSpan - other.m_angleSpan))
            return true;

        return false;
    }

    void emitChangedSignal(QPieSlice *s)
    {
        emit s->changed();
    }

    static PieSliceData &data(QPieSlice *slice)
    {
        Q_ASSERT(slice);
        return *slice->d;
    }

    qreal m_value;

    Themed<QPen> m_slicePen;
    Themed<QBrush> m_sliceBrush;

    bool m_isExploded;
    qreal m_explodeDistanceFactor;

    bool m_isLabelVisible;
    QString m_labelText;
    Themed<QFont> m_labelFont;
    qreal m_labelArmLengthFactor;
    Themed<QPen> m_labelPen;

    qreal m_percentage;
    QPointF m_center;
    qreal m_radius;
    qreal m_startAngle;
    qreal m_angleSpan;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICEDATA_P_H
