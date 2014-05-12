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
import QtCommercial.Chart 1.1

Rectangle {
    anchors.fill: parent

    //![1]
    ChartView {
        title: "NHL All-Star Team Players"
        anchors.fill: parent
        antialiasing: true

        ValueAxis {
            id: valueAxis
            min: 2000
            max: 2011
            tickCount: 12
            labelFormat: "%.0f"
        }

        AreaSeries {
            name: "Russian"
            color: "#FFD52B1E"
            borderColor: "#FF0039A5"
            borderWidth: 3
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
        // ...
        //![1]

        AreaSeries {
            name: "Swedish"
            color: "#AF005292"
            borderColor: "#AFFDCA00"
            borderWidth: 3
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
            color: "#00357F"
            borderColor: "#FEFEFE"
            borderWidth: 3
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
}
