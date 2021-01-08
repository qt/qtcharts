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

    ScatterSeries {
        name: "ScatterSeries"
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
        XYPoint { x: 8; y: 12.9 }
        XYPoint { x: 9; y: 19.2 }
    }
}
