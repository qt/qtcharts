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

Row {
    anchors.fill: parent
    spacing: 5
    property variant axis

    Flow {
        id: flow
        spacing: 5
        flow: Flow.TopToBottom

        Button {
            text: "axis visible"
            onClicked: axis.visible = !axis.visible;
        }
        Button {
            text: "axis grid visible"
            onClicked: axis.gridVisible = !axis.gridVisible;
        }
        Button {
            text: "axis color"
            onClicked: axis.color = main.nextColor();
        }
        Button {
            text: "axis labels color"
            onClicked: axis.labelsColor = main.nextColor();
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
            text: "axis ticks count +"
            onClicked: axis.ticksCount++;
        }
        Button {
            text: "axis ticks count -"
            onClicked: axis.ticksCount--;
        }
        Button {
            text: "axis nice nmb"
            onClicked: axis.niceNumbersEnabled = !axis.niceNumbersEnabled;
        }
    }

    FontEditor {
        id: fontEditor
        fontDescription: "axis"
        function editedFont() {
            return axis.labelsFont;
        }
    }
}
