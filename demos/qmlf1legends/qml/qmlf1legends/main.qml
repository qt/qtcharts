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

import QtQuick 1.1
import QtCommercial.Chart 1.1

Rectangle {
    width: 360
    height: 360
    property int currentIndex: -1

    //![1]
    ChartView {
        id: chartView
        title: "Driver Speeds, lap 1"
        anchors.fill: parent
        legend.alignment: Qt.AlignTop
        animationOptions: ChartView.SeriesAnimations
    }
    //![1]

    //![2]
    // An example XmlListModel containing F1 legend drivers' speeds at speed traps
    SpeedsXml {
        id: speedsXml
        onStatusChanged: {
            if (status == XmlListModel.Ready) {
                timer.start();
            }
        }
    }
    //![2]

    //![3]
    // A timer to mimic refreshing the data dynamically
    Timer {
        id: timer
        interval: 700
        repeat: true
        triggeredOnStart: true
        running: false
        onTriggered: {
            currentIndex++;
            if (currentIndex < speedsXml.count) {
                // Check if there is a series for the data already (we are using driver name to identify series)
                var lineSeries = chartView.series(speedsXml.get(currentIndex).driver);
                if (!lineSeries) {
                    lineSeries = chartView.createSeries(ChartView.SeriesTypeLine, speedsXml.get(currentIndex).driver);
                    chartView.axisY().min = 0;
                    chartView.axisY().max = 250;
                    chartView.axisY().tickCount = 6;
                    chartView.axisY().title = "speed (kph)";
                    chartView.axisX().title = "speed trap";
                    chartView.axisX().labelFormat = "%.0f";
                }
                lineSeries.append(speedsXml.get(currentIndex).speedTrap, speedsXml.get(currentIndex).speed);

                if (speedsXml.get(currentIndex).speedTrap > 3) {
                    chartView.axisX().max = Number(speedsXml.get(currentIndex).speedTrap) + 1;
                    chartView.axisX().min = chartView.axisX().max - 5;
                } else {
                    chartView.axisX().max = 5;
                    chartView.axisX().min = 0;
                }
                chartView.axisX().tickCount = chartView.axisX().max - chartView.axisX().min + 1;
            } else {
                // No more data, change x-axis range to show all the data
                timer.stop();
                chartView.animationOptions = ChartView.AllAnimations;
                chartView.axisX().min = 0;
                chartView.axisX().max = speedsXml.get(currentIndex - 1).speedTrap;
            }
        }
    }
    //![3]
}
