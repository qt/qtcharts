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

Item {
    width: 400
    height: 300
    property int __activeIndex: 1
    property real __intervalCoefficient: 0

    //![1]
    ChartView {
        id: chartView
        anchors.fill: parent
        title: "Wheel of fortune"
        legend.visible: false
        antialiasing: true

        PieSeries {
            id: wheelOfFortune
            horizontalPosition: 0.3
        }

        SplineSeries {
            id: splineSeries
        }

        ScatterSeries {
            id: scatterSeries
        }
    }
    //![1]

    //![2]
    Component.onCompleted: {
        __intervalCoefficient = Math.random() + 0.1;

        for (var i = 0; i < 20; i++)
            wheelOfFortune.append("", 1);

        var interval = 1;
        for (var j = 0; interval < 800; j++) {
            interval = __intervalCoefficient * j * j;
            splineSeries.append(j, interval);
        }
        chartView.axisX(scatterSeries).max = j;
        chartView.axisY(scatterSeries).max = 1000;
    }
    //![2]

    Timer {
        triggeredOnStart: true
        running: true
        repeat: true
        interval: 100
        onTriggered: {
            var index = __activeIndex % wheelOfFortune.count;
            if (interval < 700) {
                //![3]
                wheelOfFortune.at(index).exploded = false;
                __activeIndex++;
                index = __activeIndex % wheelOfFortune.count;
                wheelOfFortune.at(index).exploded = true;
                //![3]
                interval = splineSeries.at(__activeIndex).y;
                //![4]
                scatterSeries.clear();
                scatterSeries.append(__activeIndex, interval);
                scatterSeries.color = Qt.tint(scatterSeries.color, "#05FF0000");
                scatterSeries.markerSize += 0.5;
                //![4]
            } else {
                //![5]
                // Switch the colors of the slice and the border
                wheelOfFortune.at(index).borderWidth = 2;
                var borderColor = wheelOfFortune.at(index).borderColor;
                wheelOfFortune.at(index).borderColor = wheelOfFortune.at(index).color;
                wheelOfFortune.at(index).color = borderColor;
                //![5]
            }
        }
    }
}
