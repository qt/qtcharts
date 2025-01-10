// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef STACKEDDRILLDOWNCHART_H
#define STACKEDDRILLDOWNCHART_H

#include "stackeddrilldownseries.h"

#include <QChart>

QT_FORWARD_DECLARE_CLASS(QBarCategoryAxis)
QT_FORWARD_DECLARE_CLASS(QValueAxis)

//! [1]
class StackedDrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit StackedDrilldownChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});

    void changeSeries(StackedDrilldownSeries *series);

public slots:
    void handleClicked(int index, QBarSet *);

private:
    StackedDrilldownSeries *m_currentSeries = nullptr;
    QBarCategoryAxis *m_axisX = nullptr;
    QValueAxis *m_axisY = nullptr;
};
//! [1]

#endif
