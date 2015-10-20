/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
        for (var i = 0; i < selectedSeries.upperSeries.count; i++ ) {
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

