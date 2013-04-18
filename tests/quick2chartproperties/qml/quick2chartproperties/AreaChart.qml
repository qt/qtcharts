/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

import QtQuick 2.0
import QtCommercial.Chart 1.1

ChartView {
    title: "area series"
    anchors.fill: parent
    animationOptions: ChartView.SeriesAnimations

    property variant series: areaSeries

    AreaSeries {
        id: areaSeries
        name: "area 1"

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

        onNameChanged:              console.log(name + ".onNameChanged: " + name);
        onVisibleChanged:           console.log(name + ".onVisibleChanged: " + visible);
        onOpacityChanged:           console.log(name + ".onOpacityChanged: " + opacity);
        onClicked:                  console.log(name + ".onClicked: " + point.x + ", " + point.y);
        onSelected:                 console.log(name + ".onSelected");
        onColorChanged:             console.log(name + ".onColorChanged: " + color);
        onBorderColorChanged:       console.log(name + ".onBorderColorChanged: " + borderColor);
        onBorderWidthChanged:       console.log(name + ".onBorderChanged: " + borderWidth);
//        onCountChanged:             console.log(name + ".onCountChanged: " + count);
        onHovered:                  console.log("lineSeries.onHovered:" + point.x + "," + point.y + " " + state);
    }

    AreaSeries {
        name: "area 2"

        upperSeries: LineSeries {
            XYPoint { x: 0; y: 0.5 }
            XYPoint { x: 1; y: 1.5 }
            XYPoint { x: 2; y: 0.3 }
            XYPoint { x: 3; y: 1.5 }
            XYPoint { x: 4; y: 0.1 }
            XYPoint { x: 5; y: 0.3 }
            XYPoint { x: 6; y: 1.2 }
            XYPoint { x: 7; y: 1.3 }
            XYPoint { x: 8; y: 0.2 }
            XYPoint { x: 9; y: 0.1 }
            XYPoint { x: 10; y: 3.2 }
            XYPoint { x: 11; y: 4.6 }
        }

        onNameChanged:              console.log(name + ".onNameChanged: " + name);
        onVisibleChanged:           console.log(name + ".onVisibleChanged: " + visible);
        onClicked:                  console.log(name + ".onClicked: " + point.x + ", " + point.y);
        onSelected:                 console.log(name + ".onSelected");
        onColorChanged:             console.log(name + ".onColorChanged: " + color);
        onBorderColorChanged:       console.log(name + ".onBorderColorChanged: " + borderColor);
    }
}
