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

#ifndef CHARTAXISY_H
#define CHARTAXISY_H

#include "chartaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAxis;
class ChartPresenter;

class ChartAxisY : public ChartAxis
{
public:
    ChartAxisY(QAxis *axis, ChartPresenter *presenter);
    ~ChartAxisY();

    AxisType axisType() const { return Y_AXIS;}

protected:
    QVector<qreal> calculateLayout() const;
    void updateGeometry();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* AXISITEM_H_ */
