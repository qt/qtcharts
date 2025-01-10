// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//![2]
import QtQuick
//![2]
import QtCharts

//![1]
ChartView {
    id: chart
    title: "Top-5 car brand shares in Finland"
    anchors.fill: parent
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    property variant othersSlice: 0

    PieSeries {
        id: pieSeries
        PieSlice { label: "Volkswagen"; value: 13.5 }
        PieSlice { label: "Toyota"; value: 10.9 }
        PieSlice { label: "Ford"; value: 8.6 }
        PieSlice { label: "Skoda"; value: 8.2 }
        PieSlice { label: "Volvo"; value: 6.8 }
    }

    Component.onCompleted: {
        // You can also manipulate slices dynamically, like append a slice or set a slice exploded
        othersSlice = pieSeries.append("Others", 52.0);
        pieSeries.find("Volkswagen").exploded = true;
    }
}

//![1]
