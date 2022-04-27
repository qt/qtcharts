/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

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

class Q_CHARTS_PRIVATE_EXPORT PolarChartCategoryAxisAngular : public PolarChartAxisAngular
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
