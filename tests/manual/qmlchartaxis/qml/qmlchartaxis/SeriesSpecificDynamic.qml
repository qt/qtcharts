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

ChartView {
    title: "series specific dynamic axes"
    id: chartView
    property int index: 0

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            switch (index) {
            case 0:
                lineAxisX.max = 6;
                lineAxisY.max = 6;
                scatterAxisX.max = 10;
                scatterAxisY.max = 10;
                break;
            case 1:
                lineAxisX.max = 10;
                lineAxisY.max = 10;
                scatterAxisX.max = 6;
                scatterAxisY.max = 6;
                break;
            default:
                chartView.axisX().max = 4;
                chartView.axisY().max = 4;
            }
            index = (index + 1) % 3;
        }
    }

    LineSeries {
        id: lineSeries
        name: "line series"
        axisX: ValueAxis { id: lineAxisX }
        axisY: ValueAxis { id: lineAxisY }
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }

    ScatterSeries {
        id: scatterSeries
        name: "scatter series"
        axisX: ValueAxis { id: scatterAxisX }
        axisY: ValueAxis { id: scatterAxisY }
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 0.5; y: 1 }
        XYPoint { x: 1; y: 2 }
        XYPoint { x: 1.5; y: 3 }
        XYPoint { x: 2; y: 4 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }
}
