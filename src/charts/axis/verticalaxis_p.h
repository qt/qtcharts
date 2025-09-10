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

#ifndef VERTICALAXIS_P_H
#define VERTICALAXIS_P_H

#include <private/cartesianchartaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT VerticalAxis : public CartesianChartAxis
{
public:
    VerticalAxis(QAbstractAxis *axis, QGraphicsItem *item = nullptr, bool intervalAxis = false);
    ~VerticalAxis();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

protected:
    void updateGeometry() override;

private:
    void updateMinorTickGeometry();
};

QT_END_NAMESPACE

#endif // VERTICALAXIS_P_H
