// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts

//![1]
ChartView {
    id: root
    title: "Accurate Historical Data"
    anchors.fill: parent
    legend.visible: false
    antialiasing: true

    LineSeries {
        axisX: DateTimeAxis {
            format: "yyyy MMM"
            tickCount: 5
        }
        axisY: ValueAxis {
            min: 0
            max: 150
        }

        // Please note that month in JavaScript months are zero based, so 2 means March
        XYPoint { x: root.toMsecsSinceEpoch(new Date(1950, 2, 15)); y: 5 }
        XYPoint { x: root.toMsecsSinceEpoch(new Date(1970, 0, 1)); y: 50 }
        XYPoint { x: root.toMsecsSinceEpoch(new Date(1987, 12, 31)); y: 102 }
        XYPoint { x: root.toMsecsSinceEpoch(new Date(1998, 7, 1)); y: 100 }
        XYPoint { x: root.toMsecsSinceEpoch(new Date(2012, 8, 2)); y: 110 }
    }

    // DateTimeAxis is based on QDateTimes so we must convert our JavaScript dates to
    // milliseconds since epoch to make them match the DateTimeAxis values
    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }
}
//![1]
