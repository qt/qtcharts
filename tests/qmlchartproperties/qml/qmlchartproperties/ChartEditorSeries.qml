/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 1.0
import QtCommercial.Chart 1.1

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
