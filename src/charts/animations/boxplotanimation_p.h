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

#ifndef BOXPLOTANIMATION_P_H
#define BOXPLOTANIMATION_P_H

#include <private/chartanimation_p.h>
#include <private/boxwhiskers_p.h>
#include <private/boxwhiskersdata_p.h>
#include <private/boxwhiskersanimation_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class BoxPlotChartItem;

class BoxPlotAnimation : public QObject
{
    Q_OBJECT
public:
    BoxPlotAnimation(BoxPlotChartItem *item);
    ~BoxPlotAnimation();

    void addBox(BoxWhiskers *box);
    ChartAnimation *boxAnimation(BoxWhiskers *box);
    ChartAnimation *boxChangeAnimation(BoxWhiskers *box);

    void setAnimationStart(BoxWhiskers *box);
    void stopAll();
    void removeBoxAnimation(BoxWhiskers *box);

protected:
    BoxPlotChartItem *m_item;
    QHash<BoxWhiskers *, BoxWhiskersAnimation *> m_animations;
};

QT_CHARTS_END_NAMESPACE

#endif // BOXPLOTANIMATION_P_H
