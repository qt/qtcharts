/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

//![1]
ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark

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
        max: 1000
    }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries2
        name: "signal 2"
        axisX: axisX
        axisYRight: axisY2
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
        if (type == "line") {
            chartView.createSeries(ChartView.SeriesTypeLine, "signal 1", axisX, axisY1);
            chartView.createSeries(ChartView.SeriesTypeLine, "signal 2", axisX, axisY2);
        } else if (type == "spline") {
            chartView.createSeries(ChartView.SeriesTypeSpline, "signal 1", axisX, axisY1);
            chartView.createSeries(ChartView.SeriesTypeSpline, "signal 2", axisX, axisY2);
        } else {
            var series1 = chartView.createSeries(ChartView.SeriesTypeScatter, "signal 1", axisX, axisY1);
            series1.markerSize = 3;
            series1.borderColor = "transparent";
            var series2 = chartView.createSeries(ChartView.SeriesTypeScatter, "signal 2", axisX, axisY2);
            series2.markerSize = 3;
            series2.borderColor = "transparent";
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
