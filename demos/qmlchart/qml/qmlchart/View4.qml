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

Rectangle {
    anchors.fill: parent

    //![1]
    ChartView {
        title: "NHL All-Star Team Players"
        anchors.fill: parent

        AreaSeries {
            axisX: CategoriesAxis {
                id: categoriesAxis
                categories: ["2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007",
                    "2008", "2009", "2010", "2011" ]
            }

            name: "Russian"
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
            lowerSeries: LineSeries {
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1; y: 0 }
                XYPoint { x: 2; y: 0 }
                XYPoint { x: 3; y: 0 }
                XYPoint { x: 4; y: 0 }
                XYPoint { x: 5; y: 0 }
                XYPoint { x: 6; y: 0 }
                XYPoint { x: 7; y: 0 }
                XYPoint { x: 8; y: 0 }
                XYPoint { x: 9; y: 0 }
                XYPoint { x: 10; y: 0 }
                XYPoint { x: 11; y: 0 }
            }
        }
        // ...
        //![1]

        AreaSeries {
            id: swedish
            name: "Swedish"
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
            lowerSeries: LineSeries {
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1; y: 0 }
                XYPoint { x: 2; y: 0 }
                XYPoint { x: 3; y: 0 }
                XYPoint { x: 4; y: 0 }
                XYPoint { x: 5; y: 0 }
                XYPoint { x: 6; y: 0 }
                XYPoint { x: 7; y: 0 }
                XYPoint { x: 8; y: 0 }
                XYPoint { x: 9; y: 0 }
                XYPoint { x: 10; y: 0 }
                XYPoint { x: 11; y: 0 }
            }
            onClicked: {
                color = "yellow";
                borderColor = "blue";
            }
        }

        AreaSeries {
            name: "Finnish"
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
            lowerSeries: LineSeries {
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1; y: 0 }
                XYPoint { x: 2; y: 0 }
                XYPoint { x: 3; y: 0 }
                XYPoint { x: 4; y: 0 }
                XYPoint { x: 5; y: 0 }
                XYPoint { x: 6; y: 0 }
                XYPoint { x: 7; y: 0 }
                XYPoint { x: 8; y: 0 }
                XYPoint { x: 9; y: 0 }
                XYPoint { x: 10; y: 0 }
                XYPoint { x: 11; y: 0 }
            }
            onClicked: {
                color = "white";
                borderColor = "blue";
            }
        }
    }
}
