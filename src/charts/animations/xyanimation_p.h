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

#ifndef XYANIMATION_P_H
#define XYANIMATION_P_H

#include <private/chartanimation_p.h>
#include <QtCore/QPointF>

QT_CHARTS_BEGIN_NAMESPACE

class XYChart;

class XYAnimation : public ChartAnimation
{
protected:
    enum Animation { AddPointAnimation, RemovePointAnimation, ReplacePointAnimation, NewAnimation };
public:
    XYAnimation(XYChart *item);
    ~XYAnimation();
    void setup(const QVector<QPointF> &oldPoints, const QVector<QPointF> &newPoints, int index = -1);
    Animation animationType() const { return m_type; };

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const;
    void updateCurrentValue(const QVariant &value);
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    XYChart *chartItem() { return m_item; }
protected:
    Animation m_type;
    bool m_dirty;
    int m_index;
private:
    XYChart *m_item;
    QVector<QPointF> m_oldPoints;
    QVector<QPointF> m_newPoints;
};

QT_CHARTS_END_NAMESPACE

#endif
