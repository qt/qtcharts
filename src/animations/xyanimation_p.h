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

#ifndef XYANIMATION_P_H
#define XYANIMATION_P_H

#include "chartanimation_p.h"
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class XYChart;

class XYAnimation : public ChartAnimation
{
public:
    enum Animation { AddPointAnimation, RemovePointAnimation, ReplacePointAnimation, NewAnimation };
    XYAnimation(XYChart *item);
    ~XYAnimation();
    void setValues(const QVector<QPointF> &oldPoints, const QVector<QPointF> &newPoints,int index);
    void setAnimationType(Animation type);
    Animation animationType() const { return m_type; };

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress ) const;
    void updateCurrentValue (const QVariant &value );
    void updateState( QAbstractAnimation::State newState, QAbstractAnimation::State oldState );
private:
    XYChart *m_item;
    QVector<QPointF> m_oldPoints;
    QVector<QPointF> m_newPoints;
    int m_index;
    bool m_dirty;
    Animation m_type;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
