// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>

QT_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif
