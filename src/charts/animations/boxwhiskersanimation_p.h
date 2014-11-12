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

#ifndef BOXWHISKERSANIMATION_P_H
#define BOXWHISKERSANIMATION_P_H

#include <private/chartanimation_p.h>
#include <private/boxwhiskers_p.h>
#include <private/boxwhiskersdata_p.h>

QT_CHARTS_BEGIN_NAMESPACE

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

QT_CHARTS_END_NAMESPACE

#endif // BOXWHISKERSANIMATION_P_H
