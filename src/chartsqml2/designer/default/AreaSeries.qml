// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    width: 300
    height: 300

    AreaSeries {
        name: "AreaSeries"
        upperSeries: LineSeries {
            XYPoint { x: 0; y: 1.5 }
            XYPoint { x: 1; y: 3 }
            XYPoint { x: 3; y: 4.3 }
            XYPoint { x: 6; y: 1.1 }
        }
    }
}
