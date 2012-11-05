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
import QtCommercial.Chart 1.2

ChartView {
    id: chartView
    title: "Government Finance Taxes in Finland"
    legend.visible: false
    signal entered(string seriesName)
    signal exited(string seriesName)
    margins.top: 10
    margins.bottom: 0

    ValueAxis {
        id: axisX
        min: 2005
        max: 2011
        tickCount: 7
        labelFormat: "%.0f"
    }

    ValueAxis {
        id: axisY
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
            XYPoint { x: 2005; y: 35771 }
            XYPoint { x: 2006; y: 36822 }
            XYPoint { x: 2007; y: 39220 }
            XYPoint { x: 2008; y: 39624 }
            XYPoint { x: 2009; y: 34061 }
            XYPoint { x: 2010; y: 34680 }
            XYPoint { x: 2011; y: 39180 }
        }
        lowerSeries: LineSeries {
            XYPoint { x: 2005; y: 0 }
            XYPoint { x: 2006; y: 0 }
            XYPoint { x: 2007; y: 0 }
            XYPoint { x: 2008; y: 0 }
            XYPoint { x: 2009; y: 0 }
            XYPoint { x: 2010; y: 0 }
            XYPoint { x: 2011; y: 0 }
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
            XYPoint { x: 2005; y: 35771 + 14330 }
            XYPoint { x: 2006; y: 36822 + 15299 }
            XYPoint { x: 2007; y: 39220 + 16482 }
            XYPoint { x: 2008; y: 39624 + 17502 }
            XYPoint { x: 2009; y: 34061 + 17595 }
            XYPoint { x: 2010; y: 34680 + 18535 }
            XYPoint { x: 2011; y: 39180 + 19166 }
        }
        lowerSeries: stateUpper
    }
    //![1]

    AnimatedAreaSeries {
        id: socialSeries
        name: "social sec. funds"
        axisX: axisX
        axisY: axisY
        borderWidth: 0
        upperSeries: LineSeries {
            id: socialUpper
            XYPoint { x: 2005; y: 35771 + 14330 + 18865 }
            XYPoint { x: 2006; y: 36822 + 15299 + 20258 }
            XYPoint { x: 2007; y: 39220 + 16482 + 21367 }
            XYPoint { x: 2008; y: 39624 + 17502 + 22316 }
            XYPoint { x: 2009; y: 34061 + 17595 + 22026 }
            XYPoint { x: 2010; y: 34680 + 18535 + 22601 }
            XYPoint { x: 2011; y: 39180 + 19166 + 23696 }
        }
        lowerSeries: municipalUpper
    }

    AnimatedAreaSeries {
        id: euSeries
        name: "EU"
        axisX: axisX
        axisY: axisY
        borderWidth: 0
        upperSeries: LineSeries {
            id: euUpper
            XYPoint { x: 2005; y: 35771 + 14330 + 18865 + 154 }
            XYPoint { x: 2006; y: 36822 + 15299 + 20258 + 176 }
            XYPoint { x: 2007; y: 39220 + 16482 + 21367 + 200 }
            XYPoint { x: 2008; y: 39624 + 17502 + 22316 + 206 }
            XYPoint { x: 2009; y: 34061 + 17595 + 22026 + 153 }
            XYPoint { x: 2010; y: 34680 + 18535 + 22601 + 152 }
            XYPoint { x: 2011; y: 39180 + 19166 + 23696 + 190 }
        }
        lowerSeries: socialUpper
    }
}
