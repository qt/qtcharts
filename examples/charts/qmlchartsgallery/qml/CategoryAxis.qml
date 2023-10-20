// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts

//![1]
ChartView {
    title: "Numerical Data for Dummies"
    anchors.fill: parent
    legend.visible: false
    antialiasing: true

    LineSeries {
        axisY: CategoryAxis {
            min: 0
            max: 30
            CategoryRange {
                label: "critical"
                endValue: 2
            }
            CategoryRange {
                label: "low"
                endValue: 4
            }
            CategoryRange {
                label: "normal"
                endValue: 7
            }
            CategoryRange {
                label: "high"
                endValue: 15
            }
            CategoryRange {
                label: "extremely high"
                endValue: 30
            }
        }

        XYPoint { x: 0; y: 4.3 }
        XYPoint { x: 1; y: 4.1 }
        XYPoint { x: 2; y: 4.7 }
        XYPoint { x: 3; y: 3.9 }
        XYPoint { x: 4; y: 5.2 }
    }
}
//![1]
