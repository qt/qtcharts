/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

Rectangle {
    anchors.fill: parent

    //![1]
    PolarChartView {
        title: "Historical Area Series"
        anchors.fill: parent
        legend.visible: false
        antialiasing: true

        DateTimeAxis {
            id: axis1
            format: "yyyy MMM"
            tickCount: 13
        }
        ValueAxis {
            id: axis2
        }
        LineSeries {
            id: lowerLine
            axisAngular: axis1
            axisRadial: axis2

            // Please note that month in JavaScript months are zero based, so 2 means March
            XYPoint { x: toMsecsSinceEpoch(new Date(1950, 0, 1)); y: 15 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1962, 4, 1)); y: 35 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1970, 0, 1)); y: 50 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1978, 2, 1)); y: 75 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1987, 11, 1)); y: 102 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1992, 1, 1)); y: 132 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1998, 7, 1)); y: 100 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2002, 4, 1)); y: 120 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2012, 8, 1)); y: 140 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2013, 5, 1)); y: 150 }
        }
        LineSeries {
            id: upperLine
            axisAngular: axis1
            axisRadial: axis2

            // Please note that month in JavaScript months are zero based, so 2 means March
            XYPoint { x: toMsecsSinceEpoch(new Date(1950, 0, 1)); y: 30 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1962, 4, 1)); y: 55 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1970, 0, 1)); y: 80 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1978, 2, 1)); y: 105 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1987, 11, 1)); y: 125 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1992, 1, 1)); y: 160 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1998, 7, 1)); y: 140 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2002, 4, 1)); y: 140 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2012, 8, 1)); y: 170 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2013, 5, 1)); y: 200 }
        }
        AreaSeries {
            axisAngular: axis1
            axisRadial: axis2
            lowerSeries: lowerLine
            upperSeries: upperLine
        }
    }
    // DateTimeAxis is based on QDateTimes so we must convert our JavaScript dates to
    // milliseconds since epoch to make them match the DateTimeAxis values
    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }
    //![1]
}
