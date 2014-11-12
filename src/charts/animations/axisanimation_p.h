/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef AXISANIMATION_H
#define AXISANIMATION_H

#include <private/chartanimation_p.h>
#include <QtCore/QPointF>

QT_CHARTS_BEGIN_NAMESPACE

class ChartAxisElement;

class AxisAnimation: public ChartAnimation
{
public:
    enum Animation { DefaultAnimation, ZoomOutAnimation, ZoomInAnimation, MoveForwardAnimation, MoveBackwordAnimation};
    AxisAnimation(ChartAxisElement *axis);
    ~AxisAnimation();
    void setAnimationType(Animation type);
    void setAnimationPoint(const QPointF &point);
    void setValues(QVector<qreal> &oldLayout, QVector<qreal> &newLayout);
protected:
    QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const;
    void updateCurrentValue(const QVariant &value);
private:
    ChartAxisElement *m_axis;
    Animation m_type;
    QPointF m_point;
};

QT_CHARTS_END_NAMESPACE



#endif /* AXISANIMATION_H */
