// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

Item {
    anchors.fill: parent

    //![1]
    ChartView {
        title: "Two Series, Common Axes"
        anchors.fill: parent
        legend.visible: false
        antialiasing: true

        ValueAxis {
            id: axisX
            min: 0
            max: 10
            tickCount: 5
        }

        ValueAxis {
            id: axisY
            min: -0.5
            max: 1.5
        }

        LineSeries {
            id: series1
            axisX: axisX
            axisY: axisY
        }

        ScatterSeries {
            id: series2
            axisX: axisX
            axisY: axisY
        }
    }

    // Add data dynamically to the series
    Component.onCompleted: {
        for (var i = 0; i <= 10; i++) {
            series1.append(i, Math.random());
            series2.append(i, Math.random());
        }
    }
    //![1]
}
