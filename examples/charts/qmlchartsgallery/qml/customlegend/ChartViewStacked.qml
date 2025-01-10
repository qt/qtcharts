// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtCharts

ChartView {
    id: chartView

    signal entered(string seriesName)
    signal exited(string seriesName)

    title: "Government Taxes"
    legend.visible: false
    margins.top: 10
    margins.bottom: 0
    antialiasing: true

    ValueAxis {
        id: axisX
        min: 2006
        max: 2012
        tickCount: 7
        labelFormat: "%.0f"
    }

    ValueAxis {
        id: axisY
        titleText: "EUR"
        min: 0
        max: 90000
        tickCount: 10
        labelFormat: "%.0f"
    }

    AnimatedAreaSeries {
        id: stateSeries
        name: "state"
        axisX: axisX
        axisY: axisY
        borderWidth: 0
        upperSeries: LineSeries {
            id: stateUpper
            XYPoint { x: 2006; y: 33119 }
            XYPoint { x: 2007; y: 37941 }
            XYPoint { x: 2008; y: 40122 }
            XYPoint { x: 2009; y: 38991 }
            XYPoint { x: 2010; y: 34055 }
            XYPoint { x: 2011; y: 34555 }
            XYPoint { x: 2012; y: 38991 }
        }
        lowerSeries: LineSeries {
            XYPoint { x: 2006; y: 0 }
            XYPoint { x: 2007; y: 0 }
            XYPoint { x: 2008; y: 0 }
            XYPoint { x: 2009; y: 0 }
            XYPoint { x: 2010; y: 0 }
            XYPoint { x: 2011; y: 0 }
            XYPoint { x: 2012; y: 0 }
        }
    }

    //![1]
    AnimatedAreaSeries {
        id: municipalSeries
        name: "municipal"
        axisX: axisX
        axisY: axisY
        borderWidth: 0
        upperSeries: LineSeries {
            id: municipalUpper
            XYPoint { x: 2006; y: 33119 + 13443 }
            XYPoint { x: 2007; y: 37941 + 15311 }
            XYPoint { x: 2008; y: 40122 + 16552 }
            XYPoint { x: 2009; y: 38991 + 17904 }
            XYPoint { x: 2010; y: 34055 + 17599 }
            XYPoint { x: 2011; y: 34555 + 19002 }
            XYPoint { x: 2012; y: 38991 + 19177 }
        }
        lowerSeries: stateUpper
    }
    //![1]

    AnimatedAreaSeries {
        id: socialSeries
        name: "social sec."
        axisX: axisX
        axisY: axisY
        borderWidth: 0
        upperSeries: LineSeries {
            id: socialUpper
            XYPoint { x: 2006; y: 33119 + 13443 + 18855 }
            XYPoint { x: 2007; y: 37941 + 15311 + 20238 }
            XYPoint { x: 2008; y: 40122 + 16552 + 21347 }
            XYPoint { x: 2009; y: 38991 + 17904 + 22376 }
            XYPoint { x: 2010; y: 34055 + 17599 + 22076 }
            XYPoint { x: 2011; y: 34555 + 19002 + 22631 }
            XYPoint { x: 2012; y: 38991 + 19177 + 23686 }
        }
        lowerSeries: municipalUpper
    }
}
