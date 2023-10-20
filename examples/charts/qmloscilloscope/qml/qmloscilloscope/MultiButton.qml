// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    id: button

    property string text: "Option: "
    property variant items: ["first"]
    property int currentSelection: 0

    signal selectionChanged(variant selection)
    signal clicked

    implicitWidth: buttonText.implicitWidth + 5
    implicitHeight: buttonText.implicitHeight + 10

    Rectangle {
        anchors.fill: parent
        radius: 3
        gradient: button.enabled ? enabledGradient : disabledGradient

        Gradient {
            id: enabledGradient
            GradientStop { position: 0.0; color: "#eeeeee" }
            GradientStop { position: 1.0; color: "#cccccc" }
        }
        Gradient {
            id: disabledGradient
            GradientStop { position: 0.0; color: "#444444" }
            GradientStop { position: 1.0; color: "#666666" }
        }

        Text {
            id: buttonText
            text: button.text + button.items[currentSelection]
            clip: true
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pointSize: 14
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                currentSelection = (currentSelection + 1) % items.length;
                selectionChanged(button.items[currentSelection]);
            }
        }
    }
}
