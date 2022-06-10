// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.2

Row {
    anchors.fill: parent
    spacing: 5
    property variant chartLegend

    Flow {
        spacing: 5
        flow: Flow.TopToBottom

        Button {
            text: "legend visible"
            onClicked: chartLegend.visible = !chartLegend.visible;
        }
        Button {
            text: "legend bckgrd visible"
            onClicked: chartLegend.backgroundVisible = !chartLegend.backgroundVisible;
        }
        Button {
            text: "legend color"
            onClicked: chartLegend.color = main.nextColor();
        }
        Button {
            text: "legend border color"
            onClicked: chartLegend.borderColor = main.nextColor();
        }
        Button {
            text: "legend label color"
            onClicked: chartLegend.labelColor = main.nextColor();
        }
        Button {
            text: "legend top"
            onClicked: chartLegend.alignment = Qt.AlignTop;
        }
        Button {
            text: "legend bottom"
            onClicked: chartLegend.alignment = Qt.AlignBottom;
        }
        Button {
            text: "legend left"
            onClicked: chartLegend.alignment = Qt.AlignLeft;
        }
        Button {
            text: "legend right"
            onClicked: chartLegend.alignment = Qt.AlignRight;
        }
        Button {
            text: "legend use reverse order"
            onClicked: chartLegend.reverseMarkers = !chartLegend.reverseMarkers;
        }
        Button {
            text: "legend marker shape"
            onClicked: {
                if (chartLegend.markerShape === Legend.MarkerShapeRectangle)
                    chartLegend.markerShape = Legend.MarkerShapeCircle
                else if (chartLegend.markerShape === Legend.MarkerShapeCircle)
                    chartLegend.markerShape = Legend.MarkerShapeFromSeries
                else
                    chartLegend.markerShape = Legend.MarkerShapeRectangle
            }
        }
    }

    FontEditor {
        fontDescription: "legend"
        function editedFont() {
            return chartLegend.font;
        }
    }
}
