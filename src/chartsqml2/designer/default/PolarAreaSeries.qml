/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
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
