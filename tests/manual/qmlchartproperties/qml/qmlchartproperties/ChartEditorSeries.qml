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

Flow {
    anchors.fill: parent
    property variant chart
    flow: Flow.TopToBottom
    spacing: 5

    Button {
        text: "add line"
        onClicked: addXYSeries(ChartView.SeriesTypeLine, "line");
    }
    Button {
        text: "add spline"
        onClicked: addXYSeries(ChartView.SeriesTypeSpline, "spline");
    }
    Button {
        text: "add scatter"
        onClicked: addXYSeries(ChartView.SeriesTypeScatter, "scatter");
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

    function addXYSeries(type, name) {
        var series = chart.createSeries(type, name + " " + chart.count);
        for (var i = chart.axisX().min; i < chart.axisX().max; i++) {
            var y = Math.random() * (chart.axisY().max - chart.axisY().min) + chart.axisY().min;
            var x = Math.random() + i;
            series.append(x, y);
        }
    }
}
