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
import QtCommercial.Chart 1.0

Rectangle {
    width: 360
    height: 360
    property int currentIndex: -1

    ChartView {
        id: chartView
        title: "Driver Speeds, lap 1"
        anchors.fill: parent
        legend: ChartView.LegendTop
        animationOptions: ChartView.SeriesAnimations
    }

    // An example XmlListModel containing F1 legend drivers' speeds at speed traps
    SpeedsXml {
        id: speedsXml
        onStatusChanged: {
            if (status == XmlListModel.Ready) {
                timer.start();
            }
        }
    }

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
                if (!lineSeries)
                    lineSeries = chartView.createSeries(ChartView.SeriesTypeLine, speedsXml.get(currentIndex).driver);

                lineSeries.append(currentIndex, speedsXml.get(currentIndex).speed);

                // Make the x-axis range dynamic
                if (currentIndex > 9)
                    chartView.axisX.min = currentIndex - 10;
                else
                    chartView.axisX.min = 0;
                chartView.axisX.max = currentIndex + 1;
            } else {
                // No more data, change x-axis range to show all the data
                timer.stop();
                chartView.animationOptions = ChartView.AllAnimations;
                chartView.axisX.min = 0;
                chartView.axisX.max = currentIndex + 1;
            }
            // TODO: initialising y range when creating the chart view does not work, so let's set the range here
            chartView.axisY.min = 0;
            chartView.axisY.max = 250;
        }
    }
}
