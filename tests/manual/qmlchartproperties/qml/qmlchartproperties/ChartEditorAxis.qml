// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0

Row {
    anchors.fill: parent
    spacing: 5
    property variant axis

    Flow {
        spacing: 5
        flow: Flow.TopToBottom
        height: parent.height

        Button {
            text: "axis visible"
            onClicked: axis.visible = !axis.visible;
        }
        Button {
            text: "axis line visible"
            onClicked: axis.lineVisible = !axis.lineVisible;
        }
        Button {
            text: "axis color"
            onClicked: axis.color = main.nextColor();
        }
        Button {
            text: "axis labels visible"
            onClicked: axis.labelsVisible = !axis.labelsVisible;
        }
        Button {
            text: "axis labels angle +"
            onClicked: axis.labelsAngle += 5;
        }
        Button {
            text: "axis labels angle -"
            onClicked: axis.labelsAngle -= 5;
        }
        Button {
            text: "axis labels color"
            onClicked: axis.labelsColor = main.nextColor();
        }
        Button {
            text: "axis grid visible"
            onClicked: axis.gridVisible = !axis.gridVisible;
        }
        Button {
            text: "axis minor grid visible"
            onClicked: axis.minorGridVisible = !axis.minorGridVisible;
        }
        Button {
            text: "axis grid color"
            onClicked: axis.gridLineColor = main.nextColor();
        }
        Button {
            text: "axis minor grid color"
            onClicked: axis.minorGridLineColor = main.nextColor();
        }
        Button {
            text: "axis shades visible"
            onClicked: axis.shadesVisible = !axis.shadesVisible;
        }
        Button {
            text: "axis shades color"
            onClicked: axis.shadesColor = main.nextColor();
        }
        Button {
            text: "axis shades bcolor"
            onClicked: axis.shadesBorderColor = main.nextColor();
        }
        Button {
            text: "axis title text"
            onClicked: axis.titleText = axis.titleText + "X";
        }
        Button {
            text: "axis title visible"
            onClicked: axis.titleVisible = !axis.titleVisible;
        }
        Button {
            text: "axis max +"
            onClicked: axis.max += 0.1;
        }
        Button {
            text: "axis max -"
            onClicked: axis.max -= 0.1;
        }
        Button {
            text: "axis min +"
            onClicked: axis.min += 0.1;
        }
        Button {
            text: "axis min -"
            onClicked: axis.min -= 0.1;
        }
        Button {
            text: "axis tick count +"
            onClicked: axis.tickCount++;
        }
        Button {
            text: "axis tick count -"
            onClicked: axis.tickCount--;
        }
        Button {
            text: "axis minor tick count +"
            onClicked: axis.minorTickCount++;
        }
        Button {
            text: "axis minor tick count -"
            onClicked: axis.minorTickCount--;
        }
        Button {
            text: "axis reverse"
            onClicked: axis.reverse = !axis.reverse;
        }

        FontEditor {
            id: fontEditor
            fontDescription: "axis"
            function editedFont() {
                return axis.labelsFont;
            }
        }

        FontEditor {
            id: titleFontEditor
            fontDescription: "title"
            function editedFont() {
                return axis.titleFont;
            }
        }
    }
}
