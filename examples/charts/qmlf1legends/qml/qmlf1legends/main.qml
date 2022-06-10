// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtCharts
import QtQml.Models

Item {
    width: 400
    height: 300
    property int currentIndex: -1

    //![1]
    ChartView {
        id: chartView
        title: "Driver Speeds, lap 1"
        anchors.fill: parent
        legend.alignment: Qt.AlignTop
        animationOptions: ChartView.SeriesAnimations
        antialiasing: true
    }
    //![1]

    //![2]
    // An example ListModel containing F1 legend drivers' speeds at speed traps
    SpeedsList {
        id: speedsList
        Component.onCompleted: {
            timer.start();
        }
    }
    //![2]

    //![3]
    // A timer to mimic refreshing the data dynamically
    Timer {
        id: timer
        interval: 700
        repeat: true
        triggeredOnStart: true
        running: false
        onTriggered: {
            currentIndex++;
            if (currentIndex < speedsList.count) {
                // Check if there is a series for the data already
                // (we are using driver name to identify series)
                var lineSeries = chartView.series(speedsList.get(currentIndex).driver);
                if (!lineSeries) {
                    lineSeries = chartView.createSeries(ChartView.SeriesTypeLine,
                                                        speedsList.get(currentIndex).driver);
                    chartView.axisY().min = 0;
                    chartView.axisY().max = 250;
                    chartView.axisY().tickCount = 6;
                    chartView.axisY().titleText = "speed (kph)";
                    chartView.axisX().titleText = "speed trap";
                    chartView.axisX().labelFormat = "%.0f";
                }
                lineSeries.append(speedsList.get(currentIndex).speedTrap,
                                  speedsList.get(currentIndex).speed);

                if (speedsList.get(currentIndex).speedTrap > 3) {
                    chartView.axisX().max = Number(speedsList.get(currentIndex).speedTrap) + 1;
                    chartView.axisX().min = chartView.axisX().max - 5;
                } else {
                    chartView.axisX().max = 5;
                    chartView.axisX().min = 0;
                }
                chartView.axisX().tickCount = chartView.axisX().max - chartView.axisX().min + 1;
            } else {
                // No more data, change x-axis range to show all the data
                timer.stop();
                chartView.animationOptions = ChartView.AllAnimations;
                chartView.axisX().min = 0;
                chartView.axisX().max = speedsList.get(currentIndex - 1).speedTrap;
            }
        }
    }
    //![3]
}
