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
    width: 400
    height: 300

    ChartView {
        id: chartView
        anchors.fill: parent
        title: "Oscilloscope"
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
    }

    Timer {
        interval: 16 // 60 Hz
        running: true
        repeat: true
        onTriggered: {
            dataSource.update(lineSeries1);
            dataSource.update(lineSeries2);
        }
    }

    Component.onCompleted: {
        chartView.setAxisX(axisX, lineSeries1);
        chartView.setAxisY(axisY, lineSeries1);
        chartView.setAxisX(axisX, lineSeries2);
        chartView.setAxisY(axisY, lineSeries2);
    }
}
