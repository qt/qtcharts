/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
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
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef SCATTERANIMATION_P_H
#define SCATTERANIMATION_P_H
#include "xyanimation_p.h"

QT_CHARTS_BEGIN_NAMESPACE

class ScatterChartItem;

class ScatterAnimation : public XYAnimation
{
public:
    ScatterAnimation(ScatterChartItem *item);
    ~ScatterAnimation();

protected:
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

QT_CHARTS_END_NAMESPACE

#endif
