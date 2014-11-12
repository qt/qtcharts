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

#ifndef CARTESIANCHARTLAYOUT_H
#define CARTESIANCHARTLAYOUT_H

#include <private/abstractchartlayout_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class CartesianChartLayout : public AbstractChartLayout
{
public:
    CartesianChartLayout(ChartPresenter *presenter);
    virtual ~CartesianChartLayout();

    // from AbstractChartLayout
    QRectF calculateAxisMinimum(const QRectF &minimum, const QList<ChartAxisElement *> &axes) const;
    QRectF calculateAxisGeometry(const QRectF &geometry, const QList<ChartAxisElement *> &axes) const;
};

QT_CHARTS_END_NAMESPACE

#endif // CARTESIANCHARTLAYOUT_H
