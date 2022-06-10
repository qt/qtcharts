// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    width: 300
    height: 300

    PieSeries {
        name: "PieSeries"
        PieSlice { label: "Slice1"; value: 13.5 }
        PieSlice { label: "Slice2"; value: 10.9 }
        PieSlice { label: "Slice3"; value: 8.6 }
    }
}
