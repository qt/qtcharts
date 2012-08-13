/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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
import QtCommercial.Chart 1.0

ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation

    ValuesAxis {
        id: axisY
        min: -1
        max: 3
    }

    ValuesAxis {
        id: axisX
        min: 0
        max: 1000
    }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
    }
    LineSeries {
        id: lineSeries2
        name: "signal 2"
    }

    Component.onCompleted: {
        chartView.setAxisX(axisX, lineSeries1);
        chartView.setAxisY(axisY, lineSeries1);
        chartView.setAxisX(axisX, lineSeries2);
        chartView.setAxisY(axisY, lineSeries2);
    }

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

    function changeSeriesType(type) {
        chartView.series(1).destroy();
        chartView.series(0).destroy();
        var seriesCount = 2;
        for (var i = 0; i < seriesCount; i++) {
            var series;
            if (type == "line") {
                series = scopeView.createSeries(ChartView.SeriesTypeLine, "signal " + (i + 1));
            } else if (type == "spline") {
                series = chartView.createSeries(ChartView.SeriesTypeSpline, "signal " + (i + 1));
            } else {
                series = chartView.createSeries(ChartView.SeriesTypeScatter, "signal " + (i + 1));
                series.markerSize = 3;
                series.borderColor = "transparent";
            }
            chartView.setAxisX(axisX, series);
            chartView.setAxisY(axisY, series);
        }
    }

    function setAnimations(enabled) {
        if (enabled)
            scopeView.animationOptions = ChartView.SeriesAnimations;
        else
            scopeView.animationOptions = ChartView.NoAnimation;
    }

    function changeRefreshRate(rate) {
        console.log("rate " + rate);
        refreshTimer.interval = 1 / Number(rate) * 1000;
    }
}
