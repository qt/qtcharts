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

#ifndef PIESLICEANIMATION_P_H_
#define PIESLICEANIMATION_P_H_

#include "piechartitem_p.h"
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieChartItem;
class QPieSlice;

class PieSliceAnimation : public QVariantAnimation
{
public:
    PieSliceAnimation(PieChartItem *item, QPieSlice *slice);
    ~PieSliceAnimation();
    void setValue(const PieSliceData &startValue, const PieSliceData &endValue);
    void updateValue(const PieSliceData &endValue);
    PieSliceData currentSliceValue();

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const;
    void updateCurrentValue(const QVariant &value);

private:
    PieChartItem *m_item;
    QPieSlice *m_slice;
    PieSliceData m_currentValue;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
