/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
