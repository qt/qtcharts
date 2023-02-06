// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/axisanimation_p.h>
#include <private/chartaxiselement_p.h>
#include <private/qabstractaxis_p.h>


QT_BEGIN_NAMESPACE


AxisAnimation::AxisAnimation(ChartAxisElement *axis, int duration, QEasingCurve &curve)
    : ChartAnimation(axis),
      m_axis(axis),
      m_type(DefaultAnimation)
{
    setDuration(duration);
    setEasingCurve(curve);
}

AxisAnimation::~AxisAnimation()
{
}

void AxisAnimation::setAnimationType(Animation type)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();
    m_type = type;
}

void AxisAnimation::setAnimationPoint(const QPointF &point)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();
    m_point = point;
}

void AxisAnimation::setValues(QList<qreal> &oldLayout, const QList<qreal> &newLayout)
{
    if (state() != QAbstractAnimation::Stopped) stop();

    switch (m_type) {
    case ZoomOutAnimation: {
        QRectF rect = m_axis->gridGeometry();
        oldLayout.resize(newLayout.size());

        for (int i = 0, j = oldLayout.size() - 1; i < (oldLayout.size() + 1) / 2; ++i, --j) {
            oldLayout[i] = m_axis->axis()->orientation() == Qt::Horizontal ? rect.left() : rect.bottom();
            oldLayout[j] = m_axis->axis()->orientation() == Qt::Horizontal ? rect.right() : rect.top();
        }
    }
    break;
    case ZoomInAnimation: {
        int index = qMin(oldLayout.size() * (m_axis->axis()->orientation() == Qt::Horizontal ? m_point.x() : (1 - m_point.y())), newLayout.size() - (qreal)1.0);
        oldLayout.resize(newLayout.size());

        if (index < 0)
            break;
        for (int i = 0; i < oldLayout.size(); i++)
            oldLayout[i] = oldLayout[index];
    }
    break;
    case MoveForwardAnimation: {
        oldLayout.resize(newLayout.size());

        for (int i = 0, j = i + 1; i < oldLayout.size() - 1; ++i, ++j)
            oldLayout[i] = oldLayout[j];
    }
    break;
    case MoveBackwordAnimation: {
        oldLayout.resize(newLayout.size());

        for (int i = oldLayout.size() - 1, j = i - 1; i > 0; --i, --j)
            oldLayout[i] = oldLayout[j];
    }
    break;
    default: {
        oldLayout.resize(newLayout.size());
        QRectF rect = m_axis->gridGeometry();
        for (int i = 0, j = oldLayout.size() - 1; i < oldLayout.size(); ++i, --j)
            oldLayout[i] = m_axis->axis()->orientation() == Qt::Horizontal ? rect.left() : rect.top();
    }
    break;
    }

    QVariantAnimation::KeyValues value;
    setKeyValues(value); //workaround for wrong interpolation call
    setKeyValueAt(0.0, QVariant::fromValue(oldLayout));
    setKeyValueAt(1.0, QVariant::fromValue(newLayout));
}

QVariant AxisAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress) const
{
    const auto startList = qvariant_cast<QList<qreal>>(start);
    const auto endList = qvariant_cast<QList<qreal>>(end);
    QList<qreal> result;

    Q_ASSERT(startList.size() == endList.size());

    for (int i = 0; i < startList.size(); i++) {
        const qreal value = startList[i] + ((endList[i] - startList[i]) * progress);
        result << value;
    }
    return QVariant::fromValue(result);
}


void AxisAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { // workaround
        const QList<qreal> list = qvariant_cast<QList<qreal>>(value);
        m_axis->setLayout(list);
        m_axis->updateGeometry();
    }
}

QT_END_NAMESPACE
