// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    title: "user defined reverted"

    ValueAxis {
        id: axisX
        min: 0
        max: 6
    }

    ValueAxis {
        id: axisY
        min: 0
        max: 6
    }

    ScatterSeries {
        name: "scatter series"
        axisX: axisX
        axisY: axisY
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 0.5; y: 1 }
        XYPoint { x: 1; y: 2 }
        XYPoint { x: 1.5; y: 3 }
        XYPoint { x: 2; y: 4 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }

    LineSeries {
        name: "line series"
        axisX: axisX
        axisY: axisY
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }
}
