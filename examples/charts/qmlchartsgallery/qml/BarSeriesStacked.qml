// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtCharts

//![1]
ChartView {
    title: "Stacked Bar Chart"
    anchors.fill: parent
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    StackedBarSeries {
        axisX: BarCategoryAxis { categories: ["2007", "2008", "2009", "2010", "2011", "2012" ] }
        BarSet { label: "Bob"; values: [2, 2, 3, 4, 5, 6] }
        BarSet { label: "Susan"; values: [5, 1, 2, 4, 1, 7] }
        BarSet { label: "James"; values: [3, 5, 8, 13, 5, 8] }
    }
}
//![1]
