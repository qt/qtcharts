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

ChartView {
    id: chartView
    title: "chart"
    anchors.fill: parent
    property variant series: chartView

    LineSeries {
        name: "line"
        XyPoint { x: 0; y: 0 }
        XyPoint { x: 1.1; y: 2.1 }
        XyPoint { x: 1.9; y: 3.3 }
        XyPoint { x: 2.1; y: 2.1 }
        XyPoint { x: 2.9; y: 4.9 }
        XyPoint { x: 3.4; y: 3.0 }
        XyPoint { x: 4.1; y: 3.3 }
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

    axisX.onColorChanged:               console.log("axisX.onColorChanged: " + color);
    axisX.onLabelsVisibleChanged:       console.log("axisX.onLabelsVisibleChanged: " + visible);
    axisX.onLabelsColorChanged:         console.log("axisX.onLabelsColorChanged: " + color);
    axisX.onVisibleChanged:             console.log("axisX.onVisibleChanged: " + visible);
    axisX.onGridVisibleChanged:         console.log("axisX.onGridVisibleChanged: " + visible);
    axisX.onShadesVisibleChanged:       console.log("axisX.onShadesVisibleChanged: " + visible);
    axisX.onShadesColorChanged:         console.log("axisX.onShadesColorChanged: " + color);
    axisX.onShadesBorderColorChanged:   console.log("axisX.onShadesBorderColorChanged: " + color);
    axisX.onMinChanged:                 console.log("axisX.onMinChanged: " + min);
    axisX.onMaxChanged:                 console.log("axisX.onMaxChanged: " + max);

    axisY.onColorChanged:               console.log("axisY.onColorChanged: " + color);
    axisY.onLabelsVisibleChanged:       console.log("axisY.onLabelsVisibleChanged: " + visible);
    axisY.onLabelsColorChanged:         console.log("axisY.onLabelsColorChanged: " + color);
    axisY.onVisibleChanged:             console.log("axisY.onVisibleChanged: " + visible);
    axisY.onGridVisibleChanged:         console.log("axisY.onGridVisibleChanged: " + visible);
    axisY.onShadesVisibleChanged:       console.log("axisY.onShadesVisibleChanged: " + visible);
    axisY.onShadesColorChanged:         console.log("axisY.onShadesColorChanged: " + color);
    axisY.onShadesBorderColorChanged:   console.log("axisY.onShadesBorderColorChanged: " + color);
    axisY.onMinChanged:                 console.log("axisY.onMinChanged: " + min);
    axisY.onMaxChanged:                 console.log("axisY.onMaxChanged: " + max);


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
        onOpacityChanged: if (opacity == 1.0) opacity = 0.0;
        Behavior on opacity {
            NumberAnimation { duration: 800 }
        }
    }
}
