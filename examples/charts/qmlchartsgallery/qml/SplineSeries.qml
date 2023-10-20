// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts

//![1]
ChartView {
    title: "Spline Chart"
    anchors.fill: parent
    antialiasing: true

    SplineSeries {
        name: "Spline"
        XYPoint { x: 0; y: 0.0 }
        XYPoint { x: 1.1; y: 3.2 }
        XYPoint { x: 1.9; y: 2.4 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 2.6 }
        XYPoint { x: 3.4; y: 2.3 }
        XYPoint { x: 4.1; y: 3.1 }
    }
}
//![1]
