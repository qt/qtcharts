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
import QtCommercial.Chart 1.1

//![1]
ChartView {
    id: chartViewHighlighted
    title: ""
    property variant selectedSeries
    signal clicked

    LineSeries {
        id: lineSeries

        axisX: ValueAxis {
            min: 2005
            max: 2011
            labelFormat: "%.0f"
            tickCount: 7
        }
        axisY: ValueAxis {
            id: axisY
            min: 0
            max: 40000
            niceNumbersEnabled: true
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
    }
}

