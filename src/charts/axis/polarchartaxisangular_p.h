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

#ifndef POLARCHARTAXISANGULAR_P_H
#define POLARCHARTAXISANGULAR_P_H

#include <QtCharts/qvalueaxis.h>
#include <private/polarchartaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT PolarChartAxisAngular : public PolarChartAxis
{
    Q_OBJECT

public:
    PolarChartAxisAngular(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis = false);
    ~PolarChartAxisAngular();

    Qt::Orientation orientation() const;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

    void updateGeometry() override;
    void createItems(int count) override;
    void updateMinorTickItems() override;

    qreal preferredAxisRadius(const QSizeF &maxSize) override;

public Q_SLOTS:
    void handleArrowPenChanged(const QPen &pen) override;
    void handleGridPenChanged(const QPen &pen) override;
    void handleMinorArrowPenChanged(const QPen &pen) override;
    void handleMinorGridPenChanged(const QPen &pen) override;
    void handleGridLineColorChanged(const QColor &color) override;
    void handleMinorGridLineColorChanged(const QColor &color) override;

private:
    QRectF moveLabelToPosition(qreal angularCoordinate, QPointF labelPoint, QRectF labelRect) const;
    void updateMinorTickGeometry();
};

QT_END_NAMESPACE

#endif // POLARCHARTAXISANGULAR_P_H
