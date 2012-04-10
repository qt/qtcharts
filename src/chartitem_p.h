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

#ifndef CHARTITEM_H
#define CHARTITEM_H

#include "chart_p.h"
#include "chartpresenter_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem : public QGraphicsItem, public Chart
{
    enum ChartItemTypes{ AXIS_ITEM = UserType + 1, XYLINE_ITEM };
public:
    ChartItem(ChartPresenter *presenter) : QGraphicsItem(presenter ? presenter->rootItem() : 0), Chart(presenter) {}
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTITEM_H_ */
