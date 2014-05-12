/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
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
    width: parent.width
    height: parent.height
    property int viewNumber: 1
    property int viewCount: 3

    Loader {
        id: loader
        anchors.fill: parent
        source: "View" + viewNumber + ".qml";
    }

    Rectangle {
        id: infoText
        anchors.centerIn: parent
        width: parent.width
        height: 40
        color: "black"
        Text {
            color: "white"
            anchors.centerIn: parent
            text: "Use left and right arrow keys to navigate"
        }

        Behavior on opacity {
            NumberAnimation { duration: 400 }
        }
    }

    MouseArea {
        focus: true
        anchors.fill: parent
        onClicked: {
            if (infoText.opacity > 0) {
                infoText.opacity = 0.0;
            } else {
                nextView();
            }
        }
        Keys.onPressed: {
            if (infoText.opacity > 0) {
                infoText.opacity = 0.0;
            } else {
                if (event.key == Qt.Key_Left) {
                    previousView();
                } else {
                    nextView();
                }
            }
        }
    }

    function nextView() {
        var i = viewNumber + 1;
        if (i > viewCount)
            viewNumber = 1;
        else
            viewNumber = i;
    }

    function previousView() {
        var i = viewNumber - 1;
        if (i <= 0)
            viewNumber = viewCount;
        else
            viewNumber = i;
    }
}
