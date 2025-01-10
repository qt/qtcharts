// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtCharts

Item {
    id: root
    property int __activeIndex: 1
    property real __intervalCoefficient: 0

    //![1]
    ChartView {
        id: chartView
        anchors.fill: parent
        title: "Wheel of Fortune"
        legend.visible: false
        antialiasing: true

        PieSeries {
            id: wheelOfFortune
            horizontalPosition: 0.3
        }

        SplineSeries {
            id: splineSeries
        }

        ScatterSeries {
            id: scatterSeries
        }
    }
    //![1]

    //![2]
    Component.onCompleted: {
        __intervalCoefficient = Math.random() + 0.25;

        for (var i = 0; i < 20; i++)
            wheelOfFortune.append("", 1);

        var interval = 1;
        for (var j = 0; interval < 800; j++) {
            interval = __intervalCoefficient * j * j;
            splineSeries.append(j, interval);
        }
        chartView.axisX(scatterSeries).max = j;
        chartView.axisY(scatterSeries).max = 1000;
    }
    //![2]

    Timer {
        id: timer
        property color switchColor
        triggeredOnStart: true
        running: true
        repeat: true
        interval: 100
        onTriggered: {
            var index = root.__activeIndex % wheelOfFortune.count;
            if (interval < 700) {
                //![3]
                wheelOfFortune.at(index).exploded = false;
                root.__activeIndex++;
                index = root.__activeIndex % wheelOfFortune.count;
                wheelOfFortune.at(index).exploded = true;
                //![3]
                interval = splineSeries.at(root.__activeIndex).y;
                //![4]
                scatterSeries.clear();
                scatterSeries.append(root.__activeIndex, interval);
                scatterSeries.color = Qt.tint(scatterSeries.color, "#05FF0000");
                scatterSeries.markerSize += 0.5;
                //![4]
            } else {
                //![5]
                // Switch the colors of the slice and the border
                wheelOfFortune.at(index).borderWidth = 2;
                switchColor = wheelOfFortune.at(index).borderColor;
                wheelOfFortune.at(index).borderColor = wheelOfFortune.at(index).color;
                wheelOfFortune.at(index).color = switchColor;
                //![5]
            }
        }
    }
}
