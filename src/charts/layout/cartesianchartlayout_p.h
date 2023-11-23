// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CARTESIANCHARTLAYOUT_H
#define CARTESIANCHARTLAYOUT_H

#include <private/abstractchartlayout_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT CartesianChartLayout : public AbstractChartLayout
{
public:
    CartesianChartLayout(ChartPresenter *presenter);
    virtual ~CartesianChartLayout();

    // from AbstractChartLayout
    QRectF calculateAxisMinimum(const QRectF &minimum, const QList<ChartAxisElement *> &axes) const override;
    QRectF calculateAxisGeometry(const QRectF &geometry, const QList<ChartAxisElement *> &axes,
                                 bool update = true) const override;
};

QT_END_NAMESPACE

#endif // CARTESIANCHARTLAYOUT_H
