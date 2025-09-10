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

#ifndef POLARCHARTCATEGORYAXISANGULAR_P_H
#define POLARCHARTCATEGORYAXISANGULAR_P_H

#include <private/polarchartaxisangular_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QCategoryAxis;

class Q_CHARTS_EXPORT PolarChartCategoryAxisAngular : public PolarChartAxisAngular
{
    Q_OBJECT

public:
    PolarChartCategoryAxisAngular(QCategoryAxis *axis, QGraphicsItem *item);
    ~PolarChartCategoryAxisAngular();

    virtual QList<qreal> calculateLayout() const override;
    virtual void createAxisLabels(const QList<qreal> &layout) override;

public Q_SLOTS:
    void handleCategoriesChanged();
};

QT_END_NAMESPACE

#endif // POLARCHARTCATEGORYAXISANGULAR_P_H
