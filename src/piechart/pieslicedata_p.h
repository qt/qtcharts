#ifndef PIESLICEDATA_P_H
#define PIESLICEDATA_P_H

#include <qchartglobal.h>
#include <QPen>
#include <QBrush>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

template <class T>
class Themed : public T
{
public:
    Themed():m_isThemed(true) {}

    inline T &operator=(const T &other) { return T::operator =(other); }

    inline bool operator!=(const T &other) { return T::operator !=(other); }
    inline bool operator!=(const Themed &other)
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

    bool operator!=(const PieSliceData &other)
    {
        if (m_value != other.m_value)
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
