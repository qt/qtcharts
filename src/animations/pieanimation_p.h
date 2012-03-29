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

#ifndef PIEANIMATION_P_H_
#define PIEANIMATION_P_H_

#include "chartanimation_p.h"
#include "piechartitem_p.h"
#include "piesliceanimation_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieChartItem;

class PieAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    PieAnimation(PieChartItem *item);
    ~PieAnimation();
    void updateValues(const PieLayout &newValues);
    void updateValue(QPieSlice *slice, const PieSliceData &newValue);
    void addSlice(QPieSlice *slice, const PieSliceData &endValue, bool isEmpty);
    void removeSlice(QPieSlice *slice);

public: // from QVariantAnimation
    void updateCurrentValue(const QVariant &value);

public Q_SLOTS:
    void destroySliceAnimationComplete();

private:
    PieChartItem *m_item;
    QHash<QPieSlice *, PieSliceAnimation *> m_animations;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
