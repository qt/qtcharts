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
    anchors.fill: parent

    //![1]
    ChartView {
        title: "Two Series, Common Axes"
        anchors.fill: parent
        legend.visible: false
        antialiasing: true

        ValueAxis {
            id: axisX
            min: 0
            max: 10
            tickCount: 5
        }

        ValueAxis {
            id: axisY
            min: -0.5
            max: 1.5
        }

        LineSeries {
            id: series1
            axisX: axisX
            axisY: axisY
        }

        ScatterSeries {
            id: series2
            axisX: axisX
            axisY: axisY
        }
    }

    // Add data dynamically to the series
    Component.onCompleted: {
        for (var i = 0; i <= 10; i++) {
            series1.append(i, Math.random());
            series2.append(i, Math.random());
        }
    }
    //![1]
}
