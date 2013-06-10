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

#ifndef BOXWHISKERSANIMATION_P_H
#define BOXWHISKERSANIMATION_P_H

#include "chartanimation_p.h"
#include "boxwhiskers_p.h"
#include "boxwhiskersdata_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class BoxPlotChartItem;
class BoxPlotAnimation;

class BoxWhiskersAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    BoxWhiskersAnimation(BoxWhiskers *box, BoxPlotAnimation *boxPlotAnimation);
    ~BoxWhiskersAnimation();

public: // from QVariantAnimation
    virtual QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const;
    virtual void updateCurrentValue(const QVariant &value);

    void setup(const BoxWhiskersData &startData, const BoxWhiskersData &endData);
    void setEndData(const BoxWhiskersData &endData);
    void setStartData(const BoxWhiskersData &endData);

    void moveMedianLine(bool move);

protected:
    friend class BoxPlotAnimation;
    BoxWhiskers *m_box;
    bool m_changeAnimation;
    BoxPlotAnimation *m_boxPlotAnimation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BOXWHISKERSANIMATION_P_H
