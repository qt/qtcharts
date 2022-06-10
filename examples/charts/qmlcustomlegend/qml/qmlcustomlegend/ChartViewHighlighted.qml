// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

//![1]
ChartView {
    id: chartViewHighlighted
    title: ""
    property variant selectedSeries
    signal clicked
    legend.visible: false
    margins.top: 10
    margins.bottom: 0
    antialiasing: true

    LineSeries {
        id: lineSeries

        axisX: ValueAxis {
            min: 2006
            max: 2012
            labelFormat: "%.0f"
            tickCount: 7
        }
        axisY: ValueAxis {
            id: axisY
            titleText: "EUR"
            min: 0
            max: 40000
            labelFormat: "%.0f"
            tickCount: 5
        }
    }
//![1]

    MouseArea {
        anchors.fill: parent
        onClicked: {
            chartViewHighlighted.clicked();
        }
    }

    onSelectedSeriesChanged: {
        lineSeries.clear();
        lineSeries.color = selectedSeries.color;
        var maxVal = 0.0;
        for (var i = 0; i < selectedSeries.upperSeries.count; i++) {
            var y = selectedSeries.upperSeries.at(i).y - selectedSeries.lowerSeries.at(i).y;
            lineSeries.append(selectedSeries.upperSeries.at(i).x, y);
            if (maxVal < y)
                maxVal = y;
        }
        chartViewHighlighted.title = selectedSeries.name;
        axisY.max = maxVal;
        axisY.applyNiceNumbers()
    }
}

