/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    id: chartView
    title: "Chart Title"
    anchors.fill: parent
    property variant chart: chartView

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
    onBackgroundColorChanged:          console.log("chart.onBackgroundColorChanged: " + chart.backgroundColor);
    onDropShadowEnabledChanged:        console.log("chart.onDropShadowEnabledChanged: " + enabled);
    onBackgroundRoundnessChanged:      console.log("chart.onBackgroundRoundnessChanged: " + diameter);
    onSeriesAdded:                     console.log("chart.onSeriesAdded: " + series.name);
    onSeriesRemoved:                   console.log("chart.onSeriesRemoved: " + series.name);
    onPlotAreaColorChanged:            console.log("chart.plotAreaColorChanged: " + chart.plotAreaColor);

    legend.onVisibleChanged:           console.log("legend.onVisibleChanged: " + chart.legend.visible);
    legend.onBackgroundVisibleChanged: console.log("legend.onBackgroundVisibleChanged: " + visible);
    legend.onColorChanged:             console.log("legend.onColorChanged: " + color);
    legend.onBorderColorChanged:       console.log("legend.onBorderColorChanged: " + color);
    legend.onLabelColorChanged:        console.log("legend.onLabelColorChanged: " + color);
    legend.onReverseMarkersChanged:    console.log("legend.onReverseMarkersChanged: "
                                                   + chart.legend.reverseMarkers)
    margins.onTopChanged:       console.log("chart.margins.onTopChanged: " + top );
    margins.onBottomChanged:    console.log("chart.margins.onBottomChanged: " + bottom);
    margins.onLeftChanged:      console.log("chart.margins.onLeftChanged: " + left);
    margins.onRightChanged:     console.log("chart.margins.onRightChanged: " + right);
    onPlotAreaChanged: {
        console.log("chart.onPlotAreaChanged, width: " + chartView.plotArea.width
                                                       + " height: " + chartView.plotArea.height
                                                       + " y: " + chartView.plotArea.y
                                                       + " x: " + chartView.plotArea.x);
        marginVisualizer.opacity = 1.0;
    }

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
        anchors.topMargin: chartView.margins.top
        anchors.bottomMargin: chartView.margins.bottom
        anchors.leftMargin: chartView.margins.left
        anchors.rightMargin: chartView.margins.right
        opacity: 0.0
        onOpacityChanged: if (opacity > 0.9) opacity = 0.0;
        Behavior on opacity {
            NumberAnimation { duration: 800 }
        }
    }
}