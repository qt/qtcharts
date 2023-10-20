// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef DONUTBREAKDOWNCHART_H
#define DONUTBREAKDOWNCHART_H

#include <QChart>

QT_FORWARD_DECLARE_CLASS(QPieSeries)

class DonutBreakdownChart : public QChart
{
public:
    DonutBreakdownChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    void addBreakdownSeries(QPieSeries *series, QColor color);

private:
    void recalculateAngles();
    void updateLegendMarkers();

private:
    QPieSeries *m_mainSeries = nullptr;
};

#endif
