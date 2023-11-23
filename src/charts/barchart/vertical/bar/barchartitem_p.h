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


#ifndef BARCHARTITEM_H
#define BARCHARTITEM_H

#include <private/abstractbarchartitem_p.h>
#include <QtCharts/QStackedBarSeries>
#include <QtWidgets/QGraphicsItem>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT BarChartItem : public AbstractBarChartItem
{
    Q_OBJECT
public:
    BarChartItem(QAbstractBarSeries *series, QGraphicsItem* item = 0);

private Q_SLOTS:
    void handleLabelsPositionChanged();
    void positionLabels() override;

private:
    QList<QRectF> calculateLayout() override;
    void initializeLayout(int set, int category,
                          int layoutIndex, bool resetAnimation) override;
    QPointF topLeftPoint(int set, int setCount, int category, qreal barWidth, qreal value);
    QPointF bottomRightPoint(int set, int setCount, int category, qreal barWidth, qreal value);
};

QT_END_NAMESPACE

#endif // BARCHARTITEM_H
