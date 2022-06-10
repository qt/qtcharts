// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//![1]
import QtQuick 2.0
import QtCharts 2.0

ChartView {
    width: 400
    height: 300
    theme: ChartView.ChartThemeBrownSand
    antialiasing: true

//![1]
//![2]
    PieSeries {
        id: pieSeries
        PieSlice { label: "eaten"; value: 94.9 }
        PieSlice { label: "not yet eaten"; value: 5.1 }
    }
//![2]

    Component.onCompleted: {
        if (false) {
            //![4]
            pieSeries.append("don't care", 1.1);
            //![4]

            //![5]
            pieSeries.at(0).exploded = true;
            //![5]
        }
    }

//![3]
}
//![3]
