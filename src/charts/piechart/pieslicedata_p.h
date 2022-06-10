// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef PIESLICEDATA_P_H
#define PIESLICEDATA_P_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QPieSlice>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

template <class T>
class Themed : public T
{
public:
    Themed(): m_isThemed(true) {}

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
    PieSliceData() :
        m_value(0),
        m_isExploded(false),
        m_explodeDistanceFactor(0.15),
        m_isLabelVisible(false),
        m_labelPosition(QPieSlice::LabelOutside),
        m_labelArmLengthFactor(0.15),
        m_percentage(0),
        m_radius(0),
        m_startAngle(0),
        m_angleSpan(0),
        m_holeRadius(0)
    {
    }

    bool operator!=(const PieSliceData &other) const {
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
            m_labelPosition != other.m_labelPosition ||
            !qFuzzyIsNull(m_labelArmLengthFactor - other.m_labelArmLengthFactor) ||
            m_labelBrush != other.m_labelBrush)
            return true;

        if (!qFuzzyIsNull(m_percentage - other.m_percentage) ||
            m_center != other.m_center ||
            !qFuzzyIsNull(m_radius - other.m_radius) ||
            !qFuzzyIsNull(m_startAngle - other.m_startAngle) ||
            !qFuzzyIsNull(m_angleSpan - other.m_angleSpan))
            return true;

        return false;
    }

    qreal m_value;

    Themed<QPen> m_slicePen;
    Themed<QBrush> m_sliceBrush;

    bool m_isExploded;
    qreal m_explodeDistanceFactor;

    bool m_isLabelVisible;
    QString m_labelText;
    Themed<QFont> m_labelFont;
    QPieSlice::LabelPosition m_labelPosition;
    qreal m_labelArmLengthFactor;
    Themed<QBrush> m_labelBrush;

    qreal m_percentage;
    QPointF m_center;
    qreal m_radius;
    qreal m_startAngle;
    qreal m_angleSpan;

    qreal m_holeRadius;
};

QT_END_NAMESPACE

#endif // PIESLICEDATA_P_H
