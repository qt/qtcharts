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
    m_type(NewAnimation)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
}

XYAnimation::~XYAnimation()
{
}

void XYAnimation::setAnimationType(Animation type)
{
	if (state() != QAbstractAnimation::Stopped) stop();
    m_type=type;
}

void XYAnimation::setValues(const QVector<QPointF> &oldPoints, const QVector<QPointF> &newPoints, int index)
{
	if (state() != QAbstractAnimation::Stopped) stop();

    if (m_item->isDirty()) {
        m_oldPoints = oldPoints;
        m_newPoints = newPoints;
        m_dirty=false;
    }
    else {
        if(m_dirty) {
            m_newPoints = newPoints;
            m_oldPoints = oldPoints;
            m_dirty=false;
        }
    }

    int x = m_oldPoints.count();
    int y = m_newPoints.count();

    if (abs(x - y) == 1) {
        if (y < x){
            if(!newPoints.isEmpty()) m_newPoints.insert(index,newPoints[index]);
            m_index=index;if(newPoints.isEmpty())
            m_dirty=true;
        }
        if (y > x){
            m_oldPoints.insert(index, x > 0 ? m_oldPoints[index-1] : newPoints[index]);//add
        }
    }else{
        m_newPoints=newPoints;
        m_dirty=false;
        m_oldPoints.resize(m_newPoints.size());
    }

    setKeyValueAt(0.0, qVariantFromValue(m_oldPoints));
    setKeyValueAt(1.0, qVariantFromValue(m_newPoints));

}

QVariant XYAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress ) const
{
    QVector<QPointF> startVector = qVariantValue<QVector<QPointF> >(start);
    QVector<QPointF> endVector = qVariantValue<QVector<QPointF> >(end);
    QVector<QPointF> result;

    switch (m_type) {

    case ReplacePointAnimation:
    case AddPointAnimation:
    case RemovePointAnimation:
    {
        if (startVector.count() != endVector.count())
            break;

        for(int i = 0; i < startVector.count(); i++) {
            qreal x = startVector[i].x() + ((endVector[i].x() - startVector[i].x()) * progress);
            qreal y = startVector[i].y() + ((endVector[i].y() - startVector[i].y()) * progress);
            result << QPointF(x, y);
        }

    }
        break;
    case NewAnimation: {
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
        QVector<QPointF> vector = qVariantValue<QVector<QPointF> >(value);
        m_item->setGeometryPoints(vector);
        m_item->updateGeometry();
        m_item->setDirty(true);
    }
}

void XYAnimation::updateState( QAbstractAnimation::State newState, QAbstractAnimation::State oldState )
{
	if(oldState == QAbstractAnimation::Running && newState == QAbstractAnimation::Stopped)
	{
		if(m_item->isDirty() && m_type==RemovePointAnimation){
		    if(!m_newPoints.isEmpty()) m_newPoints.remove(m_index);
			m_item->setGeometryPoints(m_newPoints);
		}
	}
}

#include "moc_chartanimation_p.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
