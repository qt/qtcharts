// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts

//![1]
ChartView {
    title: "NHL All-Star Team Players"
    anchors.fill: parent
    antialiasing: true

    // Define x-axis to be used with the series instead of default one
    ValueAxis {
        id: valueAxis
        min: 2000
        max: 2011
        tickCount: 12
        labelFormat: "%.0f"
    }

    AreaSeries {
        name: "Russian"
        axisX: valueAxis
        upperSeries: LineSeries {
            XYPoint { x: 2000; y: 1 }
            XYPoint { x: 2001; y: 1 }
            XYPoint { x: 2002; y: 1 }
            XYPoint { x: 2003; y: 1 }
            XYPoint { x: 2004; y: 1 }
            XYPoint { x: 2005; y: 0 }
            XYPoint { x: 2006; y: 1 }
            XYPoint { x: 2007; y: 1 }
            XYPoint { x: 2008; y: 4 }
            XYPoint { x: 2009; y: 3 }
            XYPoint { x: 2010; y: 2 }
            XYPoint { x: 2011; y: 1 }
        }
    }
    //![1]

    AreaSeries {
        name: "Swedish"
        axisX: valueAxis
        upperSeries: LineSeries {
            XYPoint { x: 2000; y: 1 }
            XYPoint { x: 2001; y: 1 }
            XYPoint { x: 2002; y: 3 }
            XYPoint { x: 2003; y: 3 }
            XYPoint { x: 2004; y: 2 }
            XYPoint { x: 2005; y: 0 }
            XYPoint { x: 2006; y: 2 }
            XYPoint { x: 2007; y: 1 }
            XYPoint { x: 2008; y: 2 }
            XYPoint { x: 2009; y: 1 }
            XYPoint { x: 2010; y: 3 }
            XYPoint { x: 2011; y: 3 }
        }
    }

    AreaSeries {
        name: "Finnish"
        axisX: valueAxis
        upperSeries: LineSeries {
            XYPoint { x: 2000; y: 0 }
            XYPoint { x: 2001; y: 0 }
            XYPoint { x: 2002; y: 0 }
            XYPoint { x: 2003; y: 0 }
            XYPoint { x: 2004; y: 0 }
            XYPoint { x: 2005; y: 0 }
            XYPoint { x: 2006; y: 1 }
            XYPoint { x: 2007; y: 0 }
            XYPoint { x: 2008; y: 0 }
            XYPoint { x: 2009; y: 0 }
            XYPoint { x: 2010; y: 0 }
            XYPoint { x: 2011; y: 1 }
        }
    }
}
