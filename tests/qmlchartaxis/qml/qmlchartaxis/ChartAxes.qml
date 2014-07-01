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
    title: "chart axes"

    // TODO: Do we need a property for orientation or properties "axisX" and "axisY" on ChartView
    // to make an axis the default axis for all series with no other axes defined...?
//    ValueAxis {
//        orientation: ValueAxis.AxisX
//        min: 0
//        max: 10
//    }
//    axisX: ValueAxis {
//        min: 0
//        max: 10
//    }
    // ...Now that we don't have this implementation, the following axes won't have any affect:
    ValueAxis {
        min: 0
        max: 10
    }
    ValueAxis {
        min: 0
        max: 5
    }

    LineSeries {
        name: "line series"
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }

    ScatterSeries {
        name: "scatter series"
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

//    Component.onCompleted: {
//        // You can also set the axes dynamically
//        chartView.setAxisX(axisX, scatter);
//    }
}
