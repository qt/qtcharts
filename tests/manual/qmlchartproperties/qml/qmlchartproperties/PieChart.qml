// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    id: chart
    title: "pie series"
    animationOptions: ChartView.SeriesAnimations

    property variant series: pieSeries

    PieSeries {
        id: pieSeries
        name: "pie"
        PieSlice { label: "slice1"; value: 11;
            onValueChanged:         console.log("slice.onValueChanged: " + value);
            onLabelVisibleChanged:  console.log("slice.onLabelVisibleChanged: " + labelVisible);
            onPenChanged:           console.log("slice.onPenChanged: " + pen);
            onBorderColorChanged:   console.log("slice.onBorderColorChanged: " + borderColor);
            onBorderWidthChanged:   console.log("slice.onBorderWidthChanged: " + borderWidth);
            onBrushChanged:         console.log("slice.onBrushChanged: " + brush);
            onColorChanged:         console.log("slice.onColorChanged: " + color);
            onLabelColorChanged:    console.log("slice.onLabelColorChanged: " + labelColor);
            onLabelBrushChanged:    console.log("slice.onLabelBrushChanged: " + labelBrush);
            onLabelFontChanged:     console.log("slice.onLabelFontChanged: " + labelFont);
            onPercentageChanged:    console.log("slice.onPercentageChanged: " + percentage);
            onStartAngleChanged:    console.log("slice.onStartAngleChanged: " + startAngle);
            onAngleSpanChanged:     console.log("slice.onAngleSpanChanged: " + angleSpan);
            onClicked:              console.log("slice.onClicked: " + label);
            onHovered:              console.log("slice.onHovered: " + state);
            onPressed:              console.log("slice.onPressed: " + label);
            onReleased:             console.log("slice.onReleased: " + label);
            onDoubleClicked:        console.log("slice.onDoubleClicked: " + label);
        }
        PieSlice { label: "slice2"; value: 22 }
        PieSlice { label: "slice3"; value: 33 }
        PieSlice { label: "slice4"; value: 44 }

        onNameChanged:              console.log("pieSeries.onNameChanged: " + name);
        onVisibleChanged:           console.log("pieSeries.onVisibleChanged: " + series.visible);
        onOpacityChanged:           console.log("pieSeries.onOpacityChanged: " + opacity);
        onClicked:                  console.log("pieSeries.onClicked: " + slice.label);
        onHovered:                  console.log("pieSeries.onHovered: " + slice.label);
        onAdded:                    console.log("pieSeries.onAdded: " + slices);
        onSliceAdded:               console.log("pieSeries.onSliceAdded: " + slice.label);
        onRemoved:                  console.log("pieSeries.onRemoved: " + slices);
        onSliceRemoved:             console.log("pieSeries.onSliceRemoved: " + slice.label);
        onCountChanged:             console.log("pieSeries.onCountChanged: " + count);
        onSumChanged:               console.log("pieSeries.onSumChanged: " + sum);
        onPressed:                  console.log("pieSeries.onPressed: " + slice.label);
        onReleased:                 console.log("pieSeries.onReleased: " + slice.label);
        onDoubleClicked:            console.log("pieSeries.onDoubleClicked: " + slice.label);
    }
}
