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
                lineAxisX.max = 5;
                lineAxisY.max = 5;
                scatterAxisX.max = 10;
                scatterAxisY.max = 10;
                break;
            case 1:
                lineAxisX.max = 10;
                lineAxisY.max = 10;
                scatterAxisX.max = 5;
                scatterAxisY.max = 5;
                break;
            default:
                chartView.axisX().max = 2;
                chartView.axisY().max = 2;
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
        XYPoint { x: 1.1; y: 2.1 }
        XYPoint { x: 1.9; y: 3.3 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 4.9 }
        XYPoint { x: 3.4; y: 3.0 }
        XYPoint { x: 4.1; y: 3.3 }
    }

    ScatterSeries {
        id: scatterSeries
        name: "scatter series"
        axisX: ValueAxis { id: scatterAxisX }
        axisY: ValueAxis { id: scatterAxisY }

        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        XYPoint { x: 1.9; y: 3.3 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 4.9 }
        XYPoint { x: 3.4; y: 3.0 }
        XYPoint { x: 4.1; y: 3.3 }
    }
}
