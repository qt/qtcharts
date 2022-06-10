// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.1

Flow {
    anchors.fill: parent
    property variant chart
    flow: Flow.TopToBottom
    spacing: 5

    Button {
        text: "add line"
        onClicked: addXYSeries(ChartView.SeriesTypeLine, "line", false);
    }
    Button {
        text: "add GL line"
        onClicked: addXYSeries(ChartView.SeriesTypeLine, "GL line", true);
    }
    Button {
        text: "add spline"
        onClicked: addXYSeries(ChartView.SeriesTypeSpline, "spline", false);
    }
    Button {
        text: "add scatter"
        onClicked: addXYSeries(ChartView.SeriesTypeScatter, "scatter", false);
    }
    Button {
        text: "add GL scatter"
        onClicked: addXYSeries(ChartView.SeriesTypeScatter, "GL scatter", true);
    }
    Button {
        text: "remove last"
        onClicked: {
            if (chart.count > 0)
                chart.removeSeries(chart.series(chart.count - 1));
            else
                chart.removeSeries(0);
        }
    }
    Button {
        text: "remove all"
        onClicked: chart.removeAllSeries();
    }

    function addXYSeries(type, name, openGl) {
        var series = chart.createSeries(type, name + " " + chart.count);
        var multiplier = 10;
        if (openGl) {
            series.useOpenGL = true;
            multiplier = 100;
        }
        for (var i = chart.axisX().min * multiplier; i < chart.axisX().max * multiplier; i++) {
            var y = Math.random() * (chart.axisY().max - chart.axisY().min) + chart.axisY().min;
            var x = (Math.random() + i) / multiplier;
            series.append(x, y);
        }
    }
}
