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

    LineSeries {
        name: "LineSeries"
        axisRadial: CategoryAxis {
            min: 0
            max: 20
        }
        axisAngular: ValueAxis {
            tickCount: 9
        }
        XYPoint { x: 0; y: 4.3 }
        XYPoint { x: 2; y: 4.7 }
        XYPoint { x: 4; y: 5.2 }
        XYPoint { x: 6; y: 6.1 }
        XYPoint { x: 8; y: 12.9 }
        XYPoint { x: 9; y: 19.2 }
    }
}
