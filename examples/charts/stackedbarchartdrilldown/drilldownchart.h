// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QtCharts/QChart>
#include "drilldownseries.h"

QT_BEGIN_NAMESPACE
class QBarCategoryAxis;
class QValueAxis;
QT_END_NAMESPACE

QT_USE_NAMESPACE

//! [1]
class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});

    void changeSeries(DrilldownBarSeries *series);

public Q_SLOTS:
    void handleClicked(int index, QBarSet *barset);

private:
    DrilldownBarSeries *m_currentSeries;
    QBarCategoryAxis *m_axisX;
    QValueAxis *m_axisY;
};
//! [1]

#endif // DRILLDOWNCHART_H
