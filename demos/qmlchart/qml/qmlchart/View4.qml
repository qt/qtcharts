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
import QtCommercial.Chart 1.1

Rectangle {
    anchors.fill: parent

    //![1]
    ChartView {
        title: "NHL All-Star Team Players"
        anchors.fill: parent

        CategoryAxis {
            id: categoriesAxis
            startValue: -0.5
            CategoryRange { endValue: 0.5; label: "2000" }
            CategoryRange { endValue: 1.5; label: "2001" }
            CategoryRange { endValue: 2.5; label: "2002" }
            CategoryRange { endValue: 3.5; label: "2003" }
            CategoryRange { endValue: 4.5; label: "2004" }
            CategoryRange { endValue: 5.5; label: "2005" }
            CategoryRange { endValue: 6.5; label: "2006" }
            CategoryRange { endValue: 7.5; label: "2007" }
            CategoryRange { endValue: 8.5; label: "2008" }
            CategoryRange { endValue: 9.5; label: "2009" }
            CategoryRange { endValue: 10.5; label: "2010" }
            CategoryRange { endValue: 11.5; label: "2011" }
        }

        AreaSeries {
            name: "Russian"
            axisX: categoriesAxis
            upperSeries: LineSeries {
                XYPoint { x: 0; y: 1 }
                XYPoint { x: 1; y: 1 }
                XYPoint { x: 2; y: 1 }
                XYPoint { x: 3; y: 1 }
                XYPoint { x: 4; y: 1 }
                XYPoint { x: 5; y: 0 }
                XYPoint { x: 6; y: 1 }
                XYPoint { x: 7; y: 1 }
                XYPoint { x: 8; y: 4 }
                XYPoint { x: 9; y: 3 }
                XYPoint { x: 10; y: 2 }
                XYPoint { x: 11; y: 1 }
            }
        }
        // ...
        //![1]

        AreaSeries {
            name: "Swedish"
            axisX: categoriesAxis
            upperSeries: LineSeries {
                XYPoint { x: 0; y: 1 }
                XYPoint { x: 1; y: 1 }
                XYPoint { x: 2; y: 3 }
                XYPoint { x: 3; y: 3 }
                XYPoint { x: 4; y: 2 }
                XYPoint { x: 5; y: 0 }
                XYPoint { x: 6; y: 2 }
                XYPoint { x: 7; y: 1 }
                XYPoint { x: 8; y: 2 }
                XYPoint { x: 9; y: 1 }
                XYPoint { x: 10; y: 3 }
                XYPoint { x: 11; y: 3 }
            }
        }

        AreaSeries {
            name: "Finnish"
            axisX: categoriesAxis
            upperSeries: LineSeries {
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1; y: 0 }
                XYPoint { x: 2; y: 0 }
                XYPoint { x: 3; y: 0 }
                XYPoint { x: 4; y: 0 }
                XYPoint { x: 5; y: 0 }
                XYPoint { x: 6; y: 1 }
                XYPoint { x: 7; y: 0 }
                XYPoint { x: 8; y: 0 }
                XYPoint { x: 9; y: 0 }
                XYPoint { x: 10; y: 0 }
                XYPoint { x: 11; y: 1 }
            }
            onClicked: {
                color = "white";
                borderColor = "blue";
            }
        }
    }
}
