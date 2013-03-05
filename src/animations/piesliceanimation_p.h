/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef PIESLICEANIMATION_P_H
#define PIESLICEANIMATION_P_H

#include "chartanimation_p.h"
#include "piesliceitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieChartItem;

class PieSliceAnimation : public ChartAnimation
{
public:
    PieSliceAnimation(PieSliceItem *sliceItem);
    ~PieSliceAnimation();
    void setValue(const PieSliceData &startValue, const PieSliceData &endValue);
    void updateValue(const PieSliceData &endValue);
    PieSliceData currentSliceValue();

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const;
    void updateCurrentValue(const QVariant &value);

private:
    PieSliceItem *m_sliceItem;
    PieSliceData m_currentValue;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
