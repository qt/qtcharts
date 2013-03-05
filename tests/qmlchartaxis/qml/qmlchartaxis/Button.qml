/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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
