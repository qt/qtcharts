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
