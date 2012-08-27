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

ChartView {
    id: chartView
    title: "Chart Title"
    anchors.fill: parent
    property variant series: chartView

    LineSeries {
        name: "line"
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        XYPoint { x: 1.9; y: 3.3 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 4.9 }
        XYPoint { x: 3.4; y: 3.0 }
        XYPoint { x: 4.1; y: 3.3 }
    }

    onVisibleChanged:                  console.log("chart.onVisibleChanged: " + visible);
    onTitleColorChanged:               console.log("chart.onTitleColorChanged: " + color);
    onBackgroundColorChanged:          console.log("chart.onBackgroundColorChanged: " + series.backgroundColor);
    onDropShadowEnabledChanged:        console.log("chart.onDropShadowEnabledChanged: " + enabled);
    onTopMarginChanged: {
        console.log("chart.onTopMarginChanged: " + margin);
        marginVisualizer.opacity = 1.0;
    }
    onBottomMarginChanged: {
        console.log("chart.onBottomMarginChanged: " + margin);
        marginVisualizer.opacity = 1.0;
    }
    onLeftMarginChanged: {
        console.log("chart.onLeftMarginChanged: " + margin);
        marginVisualizer.opacity = 1.0;
    }
    onRightMarginChanged: {
        console.log("chart.onRightMarginChanged: " + margin);
        marginVisualizer.opacity = 1.0;
    }

    legend.onVisibleChanged:           console.log("legend.onVisibleChanged: " + series.legend.visible);
    legend.onBackgroundVisibleChanged: console.log("legend.onBackgroundVisibleChanged: " + visible);
    legend.onColorChanged:             console.log("legend.onColorChanged: " + color);
    legend.onBorderColorChanged:       console.log("legend.onBorderColorChanged: " + color);
    legend.onLabelColorChanged:        console.log("legend.onLabelColorChanged: " + color);


    ValueAxis{
        onColorChanged:               console.log("axisX.onColorChanged: " + color);
        onLabelsVisibleChanged:       console.log("axisX.onLabelsVisibleChanged: " + visible);
        onLabelsColorChanged:         console.log("axisX.onLabelsColorChanged: " + color);
        onVisibleChanged:             console.log("axisX.onVisibleChanged: " + visible);
        onGridVisibleChanged:         console.log("axisX.onGridVisibleChanged: " + visible);
        onShadesVisibleChanged:       console.log("axisX.onShadesVisibleChanged: " + visible);
        onShadesColorChanged:         console.log("axisX.onShadesColorChanged: " + color);
        onShadesBorderColorChanged:   console.log("axisX.onShadesBorderColorChanged: " + color);
        onMinChanged:                 console.log("axisX.onMinChanged: " + min);
        onMaxChanged:                 console.log("axisX.onMaxChanged: " + max);
    }
    
    ValueAxis{
        onColorChanged:               console.log("axisY.onColorChanged: " + color);
        onLabelsVisibleChanged:       console.log("axisY.onLabelsVisibleChanged: " + visible);
        onLabelsColorChanged:         console.log("axisY.onLabelsColorChanged: " + color);
        onVisibleChanged:             console.log("axisY.onVisibleChanged: " + visible);
        onGridVisibleChanged:         console.log("axisY.onGridVisibleChanged: " + visible);
        onShadesVisibleChanged:       console.log("axisY.onShadesVisibleChanged: " + visible);
        onShadesColorChanged:         console.log("axisY.onShadesColorChanged: " + color);
        onShadesBorderColorChanged:   console.log("axisY.onShadesBorderColorChanged: " + color);
        onMinChanged:                 console.log("axisY.onMinChanged: " + min);
        onMaxChanged:                 console.log("axisY.onMaxChanged: " + max);
    }

    Rectangle {
        id: marginVisualizer
        color: "transparent"
        border.color: "red"
        anchors.fill: parent
        anchors.topMargin: parent.topMargin
        anchors.bottomMargin: parent.bottomMargin
        anchors.leftMargin: parent.leftMargin
        anchors.rightMargin: parent.rightMargin
        opacity: 0.0
        onOpacityChanged: if (opacity > 0.9) opacity = 0.0;
        Behavior on opacity {
            NumberAnimation { duration: 800 }
        }
    }
}
