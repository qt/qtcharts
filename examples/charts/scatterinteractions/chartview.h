// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>

QT_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT

public:
    ChartView(QWidget *parent = 0);
    ~ChartView();

private Q_SLOTS:
    void handleClickedPoint(const QPointF &point);

private:
    QScatterSeries *m_scatter;
    QScatterSeries *m_scatter2;
};

#endif // CHARTVIEW_H
