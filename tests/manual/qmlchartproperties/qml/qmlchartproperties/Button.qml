// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0

Rectangle {
    id: button
    height: 25
    width: 140
    color: unpressedColor
    radius: 5
    property color unpressedColor: "#afafaf"

    property string text: "button"
    signal clicked

    Text {
        id: buttonText
        anchors.centerIn: parent
        text: button.text
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            button.clicked();
        }
        onPressedChanged: {
            if (pressed) {
                button.color = "#efefef";
            } else {
                button.color = unpressedColor;
            }
        }
        onPressAndHold: {
            repeatTimer.start();
        }
        onReleased: {
            repeatTimer.stop();
        }
    }

    Timer {
        id: repeatTimer
        interval: 140
        repeat: true
        triggeredOnStart: false
        running: false
        onTriggered: {
            button.clicked();
        }
    }
}
