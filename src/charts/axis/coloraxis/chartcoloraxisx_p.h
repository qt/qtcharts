// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTCOLORAXISX_H
#define CHARTCOLORAXISX_H

#include <private/horizontalaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QColorAxis;

class Q_CHARTS_EXPORT ChartColorAxisX : public HorizontalAxis
{
    Q_OBJECT
public:
    ChartColorAxisX(QColorAxis *axis, QGraphicsItem* item = 0);
    ~ChartColorAxisX();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;

protected:
    QList<qreal> calculateLayout() const override;
    void updateGeometry() override;

private:
    QColorAxis *m_axis;
};

QT_END_NAMESPACE

#endif // CHARTCOLORAXISX_H
