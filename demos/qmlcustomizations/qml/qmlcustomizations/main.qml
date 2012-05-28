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

Rectangle {
    width: parent.width
    height: parent.height
    property int __activeIndex: 1
    property real __intervalCoefficient: 0


    ChartView {
        id: chartView
        anchors.fill: parent
        title: "Wheel of fortune"
        legend: ChartView.LegendDisabled

        PieSeries {
            id: wheelOfFortune
        }

        SplineSeries {
            id: splineSeries
        }

        ScatterSeries {
            id: scatterSeries
        }
    }


    Component.onCompleted: {
        __intervalCoefficient = Math.random() + 0.1;
        console.log("__intervalCoefficient: " + __intervalCoefficient);

        for (var i = 0; i < 20; i++)
            wheelOfFortune.append("", 1);

        var interval = 1;
        for (var j = 0; interval < 800; j++) {
            interval = __intervalCoefficient * j * j;
            splineSeries.append(j, interval);
        }
        chartView.axisX.max = j;
        chartView.axisY.max = 1000;
    }

    Timer {
        triggeredOnStart: true
        running: true
        repeat: true
        interval: 100
        onTriggered: {
            var index = __activeIndex % wheelOfFortune.count;
            if (interval < 700) {
                scatterSeries.clear();
                wheelOfFortune.at(index).exploded = false;
                __activeIndex++;
                index = __activeIndex % wheelOfFortune.count;
                wheelOfFortune.at(index).exploded = true;
                interval = splineSeries.at(__activeIndex).y;
                scatterSeries.append(__activeIndex, interval);
                scatterSeries.color = Qt.tint(scatterSeries.color, "#05FF0000");
            } else {
                // Switch the colors of the slice and the border
                wheelOfFortune.at(index).borderWidth = 2;
                var borderColor = wheelOfFortune.at(index).borderColor;
                wheelOfFortune.at(index).borderColor = wheelOfFortune.at(index).color;
                wheelOfFortune.at(index).color = borderColor;
            }
        }
    }
}
