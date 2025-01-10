// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtCharts

ChartView {
    title: "Box Plot Chart"
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    BoxPlotSeries {
        id: plotSeries
        name: "Income"
        BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5] }
        BoxSet { label: "Feb"; values: [5, 6, 7.5, 8.6, 11.8] }
        BoxSet { label: "Mar"; values: [3.2, 5, 5.7, 8, 9.2] }
        BoxSet { label: "Apr"; values: [3.8, 5, 6.4, 7, 8] }
        BoxSet { label: "May"; values: [4, 5, 5.2, 6, 7] }
    }
}
