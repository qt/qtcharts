/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

Rectangle {
    anchors.fill: parent

    //![1]
    ChartView {
        title: "Spline"
        anchors.fill: parent
        antialiasing: true

        SplineSeries {
            name: "SplineSeries"
            XYPoint { x: 0; y: 0.0 }
            XYPoint { x: 1.1; y: 3.2 }
            XYPoint { x: 1.9; y: 2.4 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 2.6 }
            XYPoint { x: 3.4; y: 2.3 }
            XYPoint { x: 4.1; y: 3.1 }
        }
    }
    //![1]
}
