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

#include "splineanimation_p.h"
#include "splinechartitem_p.h"
#include <QDebug>

Q_DECLARE_METATYPE(QVector<QPointF>)
Q_DECLARE_METATYPE(SplineVector)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplineAnimation::SplineAnimation(SplineChartItem* item):XYAnimation(item),
m_item(item)
{
}

SplineAnimation::~SplineAnimation()
{
}

void SplineAnimation::setup(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, QVector<QPointF> &oldControlPoints, QVector<QPointF> &newControlPoints, int index)
{
    Q_ASSERT(newPoints.count() * 2 - 2 == newControlPoints.count());

    m_type = NewAnimation;

    if (state() != QAbstractAnimation::Stopped) {
        stop();
        m_dirty=false;
    }

    if(!m_dirty) {
        m_dirty = true;
        m_oldSpline.first = oldPoints;
        m_oldSpline.second = oldControlPoints;
    }

    m_newSpline.first=newPoints;
    m_newSpline.second=newControlPoints;

    int x = m_oldSpline.first.count();
    int y = m_newSpline.first.count();

    if(x - y == 1 && index >= 0 && y>0) {
        //remove point
        if(index>0){
            m_newSpline.first.insert(index, newPoints[index-1]);
            m_newSpline.second.insert((index -1) * 2, newPoints[index-1] );
            m_newSpline.second.insert((index -1) * 2 + 1, newPoints[index-1]);
        }else{
            m_newSpline.first.insert(index, newPoints[index]);
            m_newSpline.second.insert(index * 2, newPoints[index] );
            m_newSpline.second.insert(index * 2 + 1, newPoints[index]);
        }
        m_index=index;
        m_type = RemovePointAnimation;
    }

    if(x - y == -1 && index >= 0) {
        //add point
        if(index>0){
            m_oldSpline.first.insert(index, newPoints[index-1]);
            m_oldSpline.second.insert((index - 1) * 2, newPoints[index-1]);
            m_oldSpline.second.insert((index - 1) * 2 + 1, newPoints[index-1]);
        }else{
            m_oldSpline.first.insert(index, newPoints[index]);
            m_oldSpline.second.insert((index - 1) * 2, newPoints[index]);
            m_oldSpline.second.insert((index - 1) * 2 + 1, newPoints[index]);
        }
        m_index=index;
        m_type = AddPointAnimation;
    }

    x = m_oldSpline.first.count();
    y = m_newSpline.first.count();

    if(x != y)
    {
        m_type = NewAnimation;
    }
    else if(m_type == NewAnimation)
    {
        m_type = ReplacePointAnimation;
    }


    setKeyValueAt(0.0, qVariantFromValue(m_oldSpline));
    setKeyValueAt(1.0, qVariantFromValue(m_newSpline));
    /*
     int x = oldPoints.count();
     int y = newPoints.count();

     Q_ASSERT(newPoints.count() * 2 - 2 == newControlPoints.count());

     if (x != y && abs(x - y) != 1) {
     m_oldSpline.first = newPoints;
     m_oldSpline.second = newControlPoints;
     oldPoints.resize(newPoints.size());
     oldControlPoints.resize(newControlPoints.size());
     SplineVector oldPair;
     oldPair.first = oldPoints;
     oldPair.second = oldControlPoints;
     SplineVector newPair;
     newPair.first = newPoints;
     newPair.second = newControlPoints;
     setKeyValueAt(0.0, qVariantFromValue(oldPair));
     setKeyValueAt(1.0, qVariantFromValue(newPair));
     m_dirty = false;
     }
     else {
     if(m_dirty) {
     m_oldSpline.first = oldPoints;
     m_oldSpline.second = oldControlPoints;
     m_dirty = false;
     }
     oldPoints = newPoints;
     oldControlPoints = newControlPoints;
     if (y < x) {
     m_oldSpline.first.remove(index); //remove
     m_oldSpline.second.remove(index * 2);
     m_oldSpline.second.remove(index * 2);
     }
     if (y > x) {
     m_oldSpline.first.insert(index, x > 0 ? m_oldSpline.first[index-1] : newPoints[index]); //add
     m_oldSpline.second.insert((index - 1) * 2, x > 1 ? m_oldSpline.second[(index-2)*2] : newControlPoints[(index - 1) * 2]); //add
     m_oldSpline.second.insert((index - 1) * 2 + 1, x > 1 ? m_oldSpline.second[(index - 2) * 2 + 1] : newControlPoints[(index - 1) * 2 + 1]); //add
     }
     SplineVector newPair;
     newPair.first=newPoints;
     newPair.second=newControlPoints;
     setKeyValueAt(0.0, qVariantFromValue(m_oldSpline));
     setKeyValueAt(1.0, qVariantFromValue(newPair));
     }
     */

}

QVariant SplineAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress ) const
{

    SplineVector startPair = qVariantValue< SplineVector >(start);
    SplineVector endPair = qVariantValue< SplineVector >(end);
    SplineVector result;

    switch (animationType()) {

        case RemovePointAnimation:
        case AddPointAnimation:
        case ReplacePointAnimation:
        {
            if (startPair.first.count() != endPair.first.count())
            break;
            Q_ASSERT(startPair.first.count() * 2 - 2 == startPair.second.count());
            Q_ASSERT(endPair.first.count() * 2 - 2 == endPair.second.count());
            for(int i = 0; i < endPair.first.count(); i++) {
                qreal x = startPair.first[i].x() + ((endPair.first[i].x() - startPair.first[i].x()) * progress);
                qreal y = startPair.first[i].y() + ((endPair.first[i].y() - startPair.first[i].y()) * progress);
                result.first << QPointF(x,y);
                if (i + 1 >= endPair.first.count())
                continue;
                x = startPair.second[i * 2].x() + ((endPair.second[i * 2].x() - startPair.second[i * 2].x()) * progress);
                y = startPair.second[i * 2].y() + ((endPair.second[i * 2].y() - startPair.second[i * 2].y()) * progress);
                result.second << QPoint(x,y);
                x = startPair.second[i * 2 + 1].x() + ((endPair.second[i * 2 + 1].x() - startPair.second[i * 2 + 1].x()) * progress);
                y = startPair.second[i * 2 + 1].y() + ((endPair.second[i * 2 + 1].y() - startPair.second[i * 2 + 1].y()) * progress);
                result.second << QPoint(x,y);
            }

        }
        break;
        case NewAnimation: {
            Q_ASSERT(endPair.first.count() * 2 - 2 == endPair.second.count());
            int count = endPair.first.count()* qBound(qreal(0), progress, qreal(1));
            for(int i = 0; i < count; i++) {
                result.first << endPair.first[i];
                if(i + 1 == count)
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

    return qVariantFromValue(result);
}

void SplineAnimation::updateCurrentValue (const QVariant &value )
{
    if (state() != QAbstractAnimation::Stopped) { //workaround
        QPair<QVector<QPointF >, QVector<QPointF > > pair = qVariantValue< QPair< QVector<QPointF>, QVector<QPointF> > >(value);
        m_item->setGeometryPoints(pair.first);
        m_item->setControlGeometryPoints(pair.second);
        m_item->updateGeometry();
        m_item->setDirty(true);
        m_dirty = false;
    }
}

void SplineAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(oldState == QAbstractAnimation::Running && newState == QAbstractAnimation::Stopped)
    {
        if(m_item->isDirty() && m_type==RemovePointAnimation) {
            if(!m_newSpline.first.isEmpty()) {
                m_newSpline.first.remove(m_index);
                m_newSpline.second.remove((m_index-1) * 2);
                m_newSpline.second.remove((m_index-1) * 2);
            }
            m_item->setGeometryPoints(m_newSpline.first);
            m_item->setControlGeometryPoints(m_newSpline.second);
        }
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
