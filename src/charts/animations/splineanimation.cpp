// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/splineanimation_p.h>
#include <private/splinechartitem_p.h>
#include <QtCore/QDebug>


QT_BEGIN_NAMESPACE

SplineAnimation::SplineAnimation(SplineChartItem *item, int duration, QEasingCurve &curve)
    : XYAnimation(item, duration, curve),
      m_item(item),
      m_valid(false)
{
}

SplineAnimation::~SplineAnimation()
{
}

void SplineAnimation::setup(const QList<QPointF> &oldPoints, const QList<QPointF> &newPoints,
                            const QList<QPointF> &oldControlPoints,
                            const QList<QPointF> &newControlPoints, int index)
{
    if (newPoints.size() * 2 - 2 != newControlPoints.size() || newControlPoints.size() < 2) {
        m_valid = false;
        m_dirty = false;
        m_item->setGeometryPoints(newPoints);
        m_item->setControlGeometryPoints(newControlPoints);
        m_item->setDirty(false);
        m_item->updateGeometry();
        return;
    }

    m_type = NewAnimation;

    if (state() != QAbstractAnimation::Stopped) {
        stop();
        m_dirty = false;
    }

    if (!m_dirty) {
        m_dirty = true;
        m_oldSpline.first = oldPoints;
        m_oldSpline.second = oldControlPoints;
    }

    m_newSpline.first = newPoints;
    m_newSpline.second = newControlPoints;


    int x = m_oldSpline.first.size();
    int y = m_newSpline.first.size();

    if (x - y == 1 && index >= 0 && y > 0) {
        //remove point
        if (index > 0) {
            m_newSpline.first.insert(index, newPoints[index - 1]);
            m_newSpline.second.insert((index - 1) * 2, newPoints[index - 1]);
            m_newSpline.second.insert((index - 1) * 2 + 1, newPoints[index - 1]);
        } else {
            m_newSpline.first.insert(0, newPoints[index]);
            m_newSpline.second.insert(0, newPoints[index]);
            m_newSpline.second.insert(1, newPoints[index]);
        }
        m_index = index;
        m_type = RemovePointAnimation;
    }

    if (x - y == -1 && index >= 0) {
        //add point
        if (index > 0) {
            m_oldSpline.first.insert(index, newPoints[index - 1]);
            m_oldSpline.second.insert((index - 1) * 2, newPoints[index - 1]);
            m_oldSpline.second.insert((index - 1) * 2 + 1, newPoints[index - 1]);
        } else {
            m_oldSpline.first.insert(0, newPoints[index]);
            m_oldSpline.second.insert(0, newPoints[index]);
            m_oldSpline.second.insert(1, newPoints[index]);
        }
        m_index = index;
        m_type = AddPointAnimation;
    }

    x = m_oldSpline.first.size();
    y = m_newSpline.first.size();

    if (x != y) {
        m_type = NewAnimation;
    } else if (m_type == NewAnimation) {
        m_type = ReplacePointAnimation;
    }


    setKeyValueAt(0.0, QVariant::fromValue(m_oldSpline));
    setKeyValueAt(1.0, QVariant::fromValue(m_newSpline));

    m_valid = true;

}

QVariant SplineAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress) const
{

    SplineVector startPair = qvariant_cast< SplineVector >(start);
    SplineVector endPair = qvariant_cast< SplineVector >(end);
    SplineVector result;

    switch (animationType()) {
    case RemovePointAnimation:
    case AddPointAnimation:
    case ReplacePointAnimation: {
        if (startPair.first.size() != endPair.first.size())
            break;
        Q_ASSERT(startPair.first.size() * 2 - 2 == startPair.second.size());
        Q_ASSERT(endPair.first.size() * 2 - 2 == endPair.second.size());
        for (int i = 0; i < endPair.first.size(); i++) {
            qreal x = startPair.first[i].x() + ((endPair.first[i].x() - startPair.first[i].x()) * progress);
            qreal y = startPair.first[i].y() + ((endPair.first[i].y() - startPair.first[i].y()) * progress);
            result.first << QPointF(x, y);
            if (i + 1 >= endPair.first.size())
                continue;
            x = startPair.second[i * 2].x() + ((endPair.second[i * 2].x() - startPair.second[i * 2].x()) * progress);
            y = startPair.second[i * 2].y() + ((endPair.second[i * 2].y() - startPair.second[i * 2].y()) * progress);
            result.second << QPointF(x, y);
            x = startPair.second[i * 2 + 1].x() + ((endPair.second[i * 2 + 1].x() - startPair.second[i * 2 + 1].x()) * progress);
            y = startPair.second[i * 2 + 1].y() + ((endPair.second[i * 2 + 1].y() - startPair.second[i * 2 + 1].y()) * progress);
            result.second << QPointF(x, y);
        }
    }
    break;
    case NewAnimation: {
        Q_ASSERT(endPair.first.size() * 2 - 2 == endPair.second.size());
        int count = endPair.first.size() * qBound(qreal(0), progress, qreal(1));
        for (int i = 0; i < count; i++) {
            result.first << endPair.first[i];
            if (i + 1 == count)
                break;
            result.second << endPair.second[2 * i];
            result.second << endPair.second[2 * i + 1];
        }
    }
    break;
    default:
        qWarning() << "Unknown type of animation";
        break;
    }

    return QVariant::fromValue(result);
}

void SplineAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped && m_valid) { //workaround
        const auto pair = qvariant_cast<QPair<QList<QPointF>, QList<QPointF>>>(value);
        m_item->setGeometryPoints(pair.first);
        m_item->setControlGeometryPoints(pair.second);
        m_item->updateGeometry();
        m_item->setDirty(true);
        m_dirty = false;
    }
}

void SplineAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    XYAnimation::updateState(newState, oldState);

    if (oldState == QAbstractAnimation::Running && newState == QAbstractAnimation::Stopped) {
        if (m_item->isDirty() && m_type == RemovePointAnimation) {
            if (!m_newSpline.first.isEmpty()) {
                if (m_index) {
                    m_newSpline.first.remove(m_index);
                    m_newSpline.second.remove((m_index - 1) * 2);
                    m_newSpline.second.remove((m_index - 1) * 2);
                } else {
                    m_newSpline.first.remove(0);
                    m_newSpline.second.remove(0);
                    m_newSpline.second.remove(0);
                }
            }
            m_item->setGeometryPoints(m_newSpline.first);
            m_item->setControlGeometryPoints(m_newSpline.second);
        }
    }

    if (oldState == QAbstractAnimation::Stopped && newState == QAbstractAnimation::Running) {
        if (!m_valid)
            stop();
    }
}

QT_END_NAMESPACE
