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

Rectangle {
    anchors.fill: parent
    //![1]
    PolarChartView {
        title: "Two Series, Common Axes"
        anchors.fill: parent
        legend.visible: false
        antialiasing: true

        ValueAxis {
            id: axisAngular
            min: 0
            max: 20
            tickCount: 9
        }

        ValueAxis {
            id: axisRadial
            min: -0.5
            max: 1.5
        }

        SplineSeries {
            id: series1
            axisAngular: axisAngular
            axisRadial: axisRadial
            pointsVisible: true
        }

        ScatterSeries {
            id: series2
            axisAngular: axisAngular
            axisRadial: axisRadial
            markerSize: 10
        }
    }

    // Add data dynamically to the series
    Component.onCompleted: {
        for (var i = 0; i <= 20; i++) {
            series1.append(i, Math.random());
            series2.append(i, Math.random());
        }
    }
    //![1]
}
