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
        if (series && series.name == "pie") {
            seriesConnections.target = series;
            sliceConnections.target = series.at(0);
        } else {
            seriesConnections.target = null;
            sliceConnections.target = null;
        }
    }

    Connections {
        id: seriesConnections
        target: null
        onVisibleChanged:           console.log("series.onVisibleChanged: " + series.visible);
        onCountChanged:             console.log("series.onCountChanged: " + series.count);
        onSumChanged:               console.log("series.onSumChanged: " + series.sum);
    }

    Connections {
        id: sliceConnections
        target: null
        onValueChanged:             console.log("slice.onValueChanged: " + series.at(0).value);
        onLabelVisibleChanged:      console.log("slice.onLabelVisibleChanged: " + series.at(0).labelVisible);
        onPenChanged:               console.log("slice.onPenChanged: " + series.at(0).pen);
        onBorderColorChanged:       console.log("slice.onBorderColorChanged: " + series.at(0).borderColor);
        onBorderWidthChanged:       console.log("slice.onBorderWidthChanged: " + series.at(0).borderWidth);
        onBrushChanged:             console.log("slice.onBrushChanged: " + series.at(0).brush);
        onColorChanged:             console.log("slice.onColorChanged: " + series.at(0).color);
        onLabelColorChanged:        console.log("slice.onLabelColorChanged: " + series.at(0).labelColor);
        onLabelBrushChanged:        console.log("slice.onLabelBrushChanged: " + series.at(0).labelBrush);
        onLabelFontChanged:         console.log("slice.onLabelFontChanged: " + series.at(0).labelFont);
        onPercentageChanged:        console.log("slice.onPercentageChanged: " + series.at(0).percentage);
        onStartAngleChanged:        console.log("slice.onStartAngleChanged: " + series.at(0).startAngle);
        onAngleSpanChanged:         console.log("slice.onAngleSpanChanged: " + series.at(0).angleSpan);
        onClicked:                  console.log("slice.onClicked");
        onHovered:                  console.log("slice.onHovered: " + state);
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
        text: "slice label position inside"
        onClicked: series.at(0).labelPosition = PieSlice.LabelInside;
    }
    Button {
        text: "slice label position outside"
        onClicked: series.at(0).labelPosition = PieSlice.LabelOutside;
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
