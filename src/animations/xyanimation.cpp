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

#include "xyanimation_p.h"
#include "xychart_p.h"
#include <QDebug>

Q_DECLARE_METATYPE(QVector<QPointF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XYAnimation::XYAnimation(XYChart *item):ChartAnimation(item),
    m_item(item),
    m_dirty(false),
    m_type(MoveDownAnimation)
{
}

XYAnimation::~XYAnimation()
{
}

void XYAnimation::setAnimationType(Animation type)
{
    if (state() != QAbstractAnimation::Stopped) stop();
    m_type=type;
}

void XYAnimation::setValues(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, int index)
{
    if (state() != QAbstractAnimation::Stopped) stop();

    int x = oldPoints.count();
    int y = newPoints.count();

    if (x != y && abs(x - y) != 1) {
        m_oldPoints = newPoints;
        oldPoints.resize(newPoints.size());
        setKeyValueAt(0.0, qVariantFromValue(oldPoints));
        setKeyValueAt(1.0, qVariantFromValue(newPoints));
        m_dirty = false;
    }
    else {
        if (m_dirty) {
            m_oldPoints = oldPoints;
            m_dirty = false;
        }
        oldPoints = newPoints;
        if (y < x)
            m_oldPoints.remove(index); //remove
        if (y > x)
            m_oldPoints.insert(index, x > 0 ? m_oldPoints[index-1] : newPoints[index]); //add
        setKeyValueAt(0.0, qVariantFromValue(m_oldPoints));
        setKeyValueAt(1.0, qVariantFromValue(newPoints));
        Q_ASSERT(m_oldPoints.count() == newPoints.count());
    }
}

QVariant XYAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress ) const
{
    QVector<QPointF> startVector = qVariantValue<QVector<QPointF> >(start);
    QVector<QPointF> endVector = qVariantValue<QVector<QPointF> >(end);
    QVector<QPointF> result;

    switch (m_type) {

    case MoveDownAnimation: {

        if (startVector.count() != endVector.count())
            break;

        for(int i = 0; i < startVector.count(); i++) {
            qreal x = startVector[i].x() + ((endVector[i].x() - startVector[i].x()) * progress);
            qreal y = startVector[i].y() + ((endVector[i].y() - startVector[i].y()) * progress);
            result << QPointF(x, y);
        }

    }
        break;
    case LineDrawAnimation: {
        for(int i = 0; i < endVector.count() * qBound(qreal(0), progress, qreal(1)); i++)
            result << endVector[i];
    }
        break;
    default:
        qWarning() << "Unknown type of animation";
        break;
    }

    return qVariantFromValue(result);
}

void XYAnimation::updateCurrentValue (const QVariant &value)
{
    if(state()!=QAbstractAnimation::Stopped){ //workaround
        m_dirty = true;
        QVector<QPointF> vector = qVariantValue<QVector<QPointF> >(value);
        m_item->setGeometryPoints(vector);
        m_item->updateGeometry();
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
