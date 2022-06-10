// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    width: 300
    height: 300

    SplineSeries {
        name: "SplineSeries"
        XYPoint { x: 0; y: 1 }
        XYPoint { x: 3; y: 4.3 }
        XYPoint { x: 5; y: 3.1 }
        XYPoint { x: 8; y: 5.8 }
    }
}
