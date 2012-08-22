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
    id: chartView
    title: "switching axes dynamically"

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            if (lineSeries.axisX == valuesAxis1)
                lineSeries.axisX = valuesAxis2;
            else
                lineSeries.axisX = valuesAxis1;
        }
    }

    ValuesAxis {
        id: valuesAxis1
        min: 0
        max: 5
    }

    ValuesAxis {
        id: valuesAxis2
        min: 1
        max: 6
    }

    LineSeries {
        id: lineSeries
        name: "line series"
        axisX: valuesAxis1
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        XYPoint { x: 1.9; y: 3.3 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 4.9 }
        XYPoint { x: 3.4; y: 3.0 }
        XYPoint { x: 4.1; y: 3.3 }
    }
}
