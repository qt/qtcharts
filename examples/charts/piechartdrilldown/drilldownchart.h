// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
class QAbstractSeries;
class QPieSlice;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    ~DrilldownChart();
    void changeSeries(QAbstractSeries *series);

public Q_SLOTS:
    void handleSliceClicked(QPieSlice *slice);

private:
    QAbstractSeries *m_currentSeries;
};

#endif // DRILLDOWNCHART_H
