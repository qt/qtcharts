// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/xyanimation_p.h>
#include <private/xychart_p.h>
#include <QtCore/QDebug>


QT_BEGIN_NAMESPACE

XYAnimation::XYAnimation(XYChart *item, int duration, QEasingCurve &curve)
    : ChartAnimation(item),
      m_type(NewAnimation),
      m_dirty(false),
      m_index(-1),
      m_item(item)
{
    setDuration(duration);
    setEasingCurve(curve);
}

XYAnimation::~XYAnimation()
{
}

void XYAnimation::setup(const QList<QPointF> &oldPoints, const QList<QPointF> &newPoints, int index)
{
    m_type = NewAnimation;

    if (state() != QAbstractAnimation::Stopped) {
        stop();
        m_dirty = false;
    }

    if (!m_dirty) {
        m_dirty = true;
        m_oldPoints = oldPoints;
    }

    m_newPoints = newPoints;

    int x = m_oldPoints.size();
    int y = m_newPoints.size();
    int diff = x - y;
    int requestedDiff = oldPoints.size() - y;

    // m_oldPoints can be whatever between 0 and actual points count if new animation setup
    // interrupts a previous animation, so only do remove and add animations if both
    // stored diff and requested diff indicate add or remove. Also ensure that index is not
    // invalid.
    if (diff == 1 && requestedDiff == 1 && index >= 0 && y > 0 && index <= y) {
        //remove point
        m_newPoints.insert(index, index > 0 ? newPoints[index - 1] : newPoints[index]);
        m_index = index;
        m_type = RemovePointAnimation;
    }

    if (diff == -1 && requestedDiff == -1 && index >= 0 && index <= x) {
        //add point
        m_oldPoints.insert(index, index > 0 ? newPoints[index - 1] : newPoints[index]);
        m_index = index;
        m_type = AddPointAnimation;
    }

    x = m_oldPoints.size();
    y = m_newPoints.size();

    if (x != y)
        m_type = NewAnimation;
    else if (m_type == NewAnimation)
        m_type = ReplacePointAnimation;

    setKeyValueAt(0.0, QVariant::fromValue(m_oldPoints));
    setKeyValueAt(1.0, QVariant::fromValue(m_newPoints));
}

QVariant XYAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress) const
{
    const auto startList = qvariant_cast<QList<QPointF>>(start);
    const auto endList = qvariant_cast<QList<QPointF>>(end);
    QList<QPointF> result;

    switch (m_type) {

    case ReplacePointAnimation:
    case AddPointAnimation:
    case RemovePointAnimation: {
        if (startList.size() != endList.size())
            break;

        for (int i = 0; i < startList.size(); i++) {
            qreal x = startList[i].x() + ((endList[i].x() - startList[i].x()) * progress);
            qreal y = startList[i].y() + ((endList[i].y() - startList[i].y()) * progress);
            result << QPointF(x, y);
        }

    }
    break;
    case NewAnimation: {
        for (int i = 0; i < endList.size() * qBound(qreal(0), progress, qreal(1)); i++)
            result << endList[i];
    }
    break;
    default:
        qWarning() << "Unknown type of animation";
        break;
    }

    return QVariant::fromValue(result);
}

void XYAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { //workaround

        const auto list = qvariant_cast<QList<QPointF>>(value);
        m_item->setGeometryPoints(list);
        m_item->updateGeometry();
        m_item->setDirty(true);
        m_dirty = false;

    }
}

void XYAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if (oldState == QAbstractAnimation::Running && newState == QAbstractAnimation::Stopped) {
        if (m_item->isDirty() && m_type == RemovePointAnimation) {
            if (!m_newPoints.isEmpty())
                m_newPoints.remove(m_index);
            m_item->setGeometryPoints(m_newPoints);
        }
    }
}

QT_END_NAMESPACE

#include "moc_chartanimation_p.cpp"
