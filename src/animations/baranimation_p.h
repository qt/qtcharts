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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef BARANIMATION_P_H
#define BARANIMATION_P_H

#include "chartanimation_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AbstractBarChartItem;

class BarAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    BarAnimation(AbstractBarChartItem *item);
    ~BarAnimation();

public: // from QVariantAnimation
    virtual QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const;
    virtual void updateCurrentValue(const QVariant &value);

    void setup(const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout);

protected:
    AbstractBarChartItem *m_item;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARANIMATION_P_H
