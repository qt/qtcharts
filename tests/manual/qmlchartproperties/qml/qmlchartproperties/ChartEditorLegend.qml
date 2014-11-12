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
    }

    FontEditor {
        fontDescription: "legend"
        function editedFont() {
            return chartLegend.font;
        }
    }
}
