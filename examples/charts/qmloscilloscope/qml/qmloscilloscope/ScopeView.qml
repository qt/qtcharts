// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtCharts

//![1]
ChartView {
    id: chartView

    property bool openGL: openGLSupported

    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark

    onOpenGLChanged: {
        if (openGLSupported) {
            var series1 = series("signal 1")
            if (series1)
                series1.useOpenGL = openGL;
            var series2 = series("signal 2")
            if (series2)
                series2.useOpenGL = openGL;
        }
    }

    ValueAxis {
        id: axisY1
        min: -1
        max: 4
    }

    ValueAxis {
        id: axisY2
        min: -10
        max: 5
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1024
    }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        axisX: axisX
        axisY: axisY1
        useOpenGL: chartView.openGL
    }
    LineSeries {
        id: lineSeries2
        name: "signal 2"
        axisX: axisX
        axisYRight: axisY2
        useOpenGL: chartView.openGL
    }
//![1]

    //![2]
    Timer {
        id: refreshTimer
        interval: 1 / 60 * 1000 // 60 Hz
        running: true
        repeat: true
        onTriggered: {
            dataSource.update(chartView.series(0));
            dataSource.update(chartView.series(1));
        }
    }
    //![2]

    //![3]
    function changeSeriesType(type) {
        chartView.removeAllSeries();

        // Create two new series of the correct type. Axis x is the same for both of the series,
        // but the series have their own y-axes to make it possible to control the y-offset
        // of the "signal sources".
        var series1
        var series2
        if (type === "line") {
            series1 = chartView.createSeries(ChartView.SeriesTypeLine, "signal 1",
                                             axisX, axisY1);
            series1.useOpenGL = chartView.openGL

            series2 = chartView.createSeries(ChartView.SeriesTypeLine, "signal 2",
                                             axisX, axisY2);
            series2.useOpenGL = chartView.openGL
        } else {
            series1 = chartView.createSeries(ChartView.SeriesTypeScatter, "signal 1",
                                             axisX, axisY1);
            series1.markerSize = 2;
            series1.borderColor = "transparent";
            series1.useOpenGL = chartView.openGL

            series2 = chartView.createSeries(ChartView.SeriesTypeScatter, "signal 2",
                                             axisX, axisY2);
            series2.markerSize = 2;
            series2.borderColor = "transparent";
            series2.useOpenGL = chartView.openGL
        }
    }

    function createAxis(min, max) {
        // The following creates a ValueAxis object that can be then set as a x or y axis for a series
        return Qt.createQmlObject("import QtQuick 2.0; import QtCharts 2.0; ValueAxis { min: "
                                  + min + "; max: " + max + " }", chartView);
    }
    //![3]

    function setAnimations(enabled) {
        if (enabled)
            chartView.animationOptions = ChartView.SeriesAnimations;
        else
            chartView.animationOptions = ChartView.NoAnimation;
    }

    function changeRefreshRate(rate) {
        refreshTimer.interval = 1 / Number(rate) * 1000;
    }
}
