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

Flow {
    id: flow
    spacing: 5
    flow: Flow.TopToBottom
    property variant series

    onSeriesChanged: {
        seriesConnections.target = series;
        sliceConnections.target = series.at(0);
    }

    Connections {
        id: seriesConnections
        ignoreUnknownSignals: true
        onVisibleChanged:           console.log("series.onVisibleChanged: " + series.visible);
        onHorizontalPositionChanged:console.log("series.onHorizontalPositionChanged: " + series.horizontalPosition);
        onVerticalPositionChanged:  console.log("series.onVerticalPositionChanged: " + series.verticalPosition);
        onSizeChanged:              console.log("series.onSizeChanged: " + series.size);
        onStartAngleChanged:        console.log("series.onStartAngleChanged: " + series.startAngle);
        onEndAngleChanged:          console.log("series.onEndAngleChanged: " + series.endAngle);
        onCountChanged:             console.log("series.onCountChanged: " + series.count);
        onSumChanged:               console.log("series.onSumChanged: " + series.sum);
    }

    Connections {
        id: sliceConnections
        ignoreUnknownSignals: true
        onValueChanged:             console.log("slice.onValueChanged: " + series.at(0).value);
        onLabelVisibleChanged:      console.log("slice.onLabelVisibleChanged: " + series.at(0).labelVisible);
        onExplodedChanged:          console.log("slice.onExplodedChanged: " + series.at(0).exploded);
        onPenChanged:               console.log("slice.onPenChanged: " + series.at(0).pen);
        onBorderColorChanged:       console.log("slice.onBorderColorChanged: " + series.at(0).borderColor);
        onBorderWidthChanged:       console.log("slice.onBorderWidthChanged: " + series.at(0).borderWidth);
        onBrushChanged:             console.log("slice.onBrushChanged: " + series.at(0).brush);
        onColorChanged:             console.log("slice.onColorChanged: " + series.at(0).color);
        onLabelColorChanged:        console.log("slice.onLabelColorChanged: " + series.at(0).labelColor);
        onLabelBrushChanged:        console.log("slice.onLabelBrushChanged: " + series.at(0).labelBrush);
        onLabelFontChanged:         console.log("slice.onLabelFontChanged: " + series.at(0).labelFont);
        onLabelArmLengthFactorChanged:  console.log("slice.onLabelArmLengthFactorChanged: " + series.at(0).labelArmLengthFactor);
        onExplodeDistanceFactorChanged: console.log("slice.onExplodeDistanceFactorChanged: " + series.at(0).explodeDistanceFactor);
        onPercentageChanged:        console.log("slice.onPercentageChanged: " + series.at(0).percentage);
        onStartAngleChanged:        console.log("slice.onStartAngleChanged: " + series.at(0).startAngle);
        onAngleSpanChanged:         console.log("slice.onAngleSpanChanged: " + series.at(0).angleSpan);
    }

    Button {
        text: "visible"
        onClicked: series.visible = !series.visible;
    }
    Button {
        text: "series hpos +"
        onClicked: series.horizontalPosition += 0.1;
    }
    Button {
        text: "series hpos -"
        onClicked: series.horizontalPosition -= 0.1;
    }
    Button {
        text: "series vpos +"
        onClicked: series.verticalPosition += 0.1;
    }
    Button {
        text: "series vpos -"
        onClicked: series.verticalPosition -= 0.1;
    }
    Button {
        text: "series size +"
        onClicked: series.size += 0.1;
    }
    Button {
        text: "series size -"
        onClicked: series.size -= 0.1;
    }
    Button {
        text: "series start angle +"
        onClicked: series.startAngle += 1.1;
    }
    Button {
        text: "series start angle -"
        onClicked: series.startAngle -= 1.1;
    }
    Button {
        text: "series end angle +"
        onClicked: series.endAngle += 1.1;
    }
    Button {
        text: "series end angle -"
        onClicked: series.endAngle -= 1.1;
    }
    Button {
        text: "slice color"
        onClicked: series.at(0).color = main.nextColor();
    }
    Button {
        text: "slice border color"
        onClicked: series.at(0).borderColor = main.nextColor();
    }
    Button {
        text: "slice border width +"
        onClicked: series.at(0).borderWidth++;
    }
    Button {
        text: "slice border width -"
        onClicked: series.at(0).borderWidth--;
    }
    Button {
        text: "slice label visible"
        onClicked: series.at(0).labelVisible = !series.at(0).labelVisible;
    }
    Button {
        text: "slice label arm len +"
        onClicked: series.at(0).labelArmLengthFactor += 0.1;
    }
    Button {
        text: "slice label arm len -"
        onClicked: series.at(0).labelArmLengthFactor -= 0.1;
    }
    Button {
        text: "slice label color"
        onClicked: series.at(0).labelColor = main.nextColor();
    }
    Button {
        text: "slice exploded"
        onClicked: series.at(0).exploded = !series.at(0).exploded;
    }
    Button {
        text: "slice explode dist +"
        onClicked: series.at(0).explodeDistanceFactor += 0.1;
    }
    Button {
        text: "slice explode dist -"
        onClicked: series.at(0).explodeDistanceFactor -= 0.1;
    }
}
