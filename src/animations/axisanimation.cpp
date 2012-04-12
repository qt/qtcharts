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

#include "axisanimation_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<qreal>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE


AxisAnimation::AxisAnimation(ChartAxis *axis): ChartAnimation(axis),
    m_axis(axis)
{
}

AxisAnimation::~AxisAnimation()
{
}

QVariant AxisAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress ) const
{
    QVector<qreal> startVector = qVariantValue<QVector<qreal> >(start);
    QVector<qreal> endVecotr = qVariantValue<QVector<qreal> >(end);
    QVector<qreal> result;

    Q_ASSERT(startVector.count() == endVecotr.count()) ;

    for(int i = 0; i < startVector.count(); i++){
           qreal value = startVector[i] + ((endVecotr[i]- startVector[i]) * progress);//qBound(0.0, progress, 1.0));
           result << value;
    }
    return qVariantFromValue(result);
}


void AxisAnimation::updateCurrentValue (const QVariant &value )
{
    if (state() != QAbstractAnimation::Stopped)//workaround
    {
        QVector<qreal> vector = qVariantValue<QVector<qreal> >(value);
        Q_ASSERT(vector.count() != 0);
        m_axis->setLayout(vector);
    }

}

QTCOMMERCIALCHART_END_NAMESPACE
