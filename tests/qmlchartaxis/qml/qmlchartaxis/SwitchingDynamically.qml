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
    id: chartView
    title: "switching axes dynamically"

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            //console.log("current axisX: " + lineSeries.axisX + " 1: " + valueAxis1 + " 2: " +valueAxis2);

            // Note: an axis is destroyed if it is not used anymore
            if (lineSeries.axisX == valueAxis1)
                lineSeries.axisX = valueAxis2;
            else if (lineSeries.axisX == valueAxis2)
                lineSeries.axisX = valueAxis3;
        }
    }

    ValueAxis {
        id: valueAxis1
        min: 0
        max: 5
    }

    ValueAxis {
        id: valueAxis2
        min: 1
        max: 6
    }

    ValueAxis {
        id: valueAxis3
        min: 2
        max: 7
    }

    LineSeries {
        id: lineSeries
        name: "line series"
        axisX: valueAxis1
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }
}
