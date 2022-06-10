// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    id: chartView
    title: "creating dyn. new series"
    property int index: 0

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            switch (index) {
            case 0:
                var count = chartView.count;
                var line = chartView.createSeries(ChartView.SeriesTypeLine, "line");
                line.append(0, 0);
                line.append(1, 1);
                line.append(2, 2);
                line.append(3, 3);
                line.append(4, 4);
                break;
            case 1:
                chartView.axisX().min = 0;
                chartView.axisX().max = 4.5;
                chartView.axisY().min = 0;
                chartView.axisY().max = 4.5;
                break;
            case 2:
                var scatter = chartView.createSeries(ChartView.SeriesTypeScatter, "scatter");
                scatter.append(0, 0);
                scatter.append(0.5, 1);
                scatter.append(1, 2);
                scatter.append(1.5, 3);
                scatter.append(2, 4);
                scatter.append(1, 1);
                scatter.append(2, 2);
                scatter.append(3, 3);
                scatter.append(4, 4);
                break;
            default:
                chartView.removeAllSeries();
            }
            index = (index + 1) % 4;
        }
    }
}
