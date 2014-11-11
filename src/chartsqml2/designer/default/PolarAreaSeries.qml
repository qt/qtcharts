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


PolarChartView {
    width: 300
    height: 300
    legend.visible: false

    ValueAxis {
        id: axis1
        tickCount: 9
    }
    ValueAxis {
        id: axis2
    }
    LineSeries {
        id: lowerLine
        axisAngular: axis1
        axisRadial: axis2

        XYPoint { x: 1; y: 5 }
        XYPoint { x: 2; y: 10 }
        XYPoint { x: 3; y: 12 }
        XYPoint { x: 4; y: 17 }
        XYPoint { x: 5; y: 20 }
    }
    LineSeries {
        id: upperLine
        axisAngular: axis1
        axisRadial: axis2

        XYPoint { x: 1; y: 5 }
        XYPoint { x: 2; y: 14 }
        XYPoint { x: 3; y: 20 }
        XYPoint { x: 4; y: 32 }
        XYPoint { x: 5; y: 35 }
    }
    AreaSeries {
        name: "AreaSeries"
        axisAngular: axis1
        axisRadial: axis2
        lowerSeries: lowerLine
        upperSeries: upperLine
    }
}
