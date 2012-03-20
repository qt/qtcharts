#ifndef QPIESLICEPRIVATE_P_H
#define QPIESLICEPRIVATE_P_H

#include "qpieslice.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieSliceData
{
public:
    PieSliceData()
    {
        m_value = 0;
        m_percentage = 0;
        m_startAngle = 0;
        m_angleSpan = 0;
        m_isExploded = false;
        m_explodeDistanceFactor = 0.15;
        m_labelVisible = false;
        m_labelArmLengthFactor = 0.15;
    }

    qreal m_value;

    QPen m_slicePen;
    QBrush m_sliceBrush;

    bool m_isExploded;
    qreal m_explodeDistanceFactor;

    bool m_labelVisible;
    QString m_labelText;
    QFont m_labelFont;
    qreal m_labelArmLengthFactor;
    QPen m_labelArmPen;

    qreal m_percentage;
    QPointF m_center;
    qreal m_radius;
    qreal m_startAngle;
    qreal m_angleSpan;
};

class QPieSlicePrivate
{
    Q_DECLARE_PUBLIC(QPieSlice)

public:
    QPieSlicePrivate(QPieSlice *parent):q_ptr(parent) {}
    ~QPieSlicePrivate() {}

    QPieSlice * const q_ptr;

    PieSliceData m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICEPRIVATE_P_H
