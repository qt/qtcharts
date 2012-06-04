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

Rectangle {
    width: parent.width
    height: parent.height
    property int viewNumber: 1

    Loader {
        id: loader
        anchors.top: parent.top
        anchors.bottom: buttons.top
        anchors.left: parent.left
        anchors.right: parent.right
        source: "View" + viewNumber + ".qml";
    }

    Row {
        id: buttons
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        Rectangle {
            height: 35
            width: 60
            color: "#c8955c"
            radius: 5
            Text {
                anchors.centerIn: parent
                text: "<"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i = viewNumber - 1;
                    if (i <= 0)
                        viewNumber = 5;
                    else
                        viewNumber = i;
                }
            }
        }
        Rectangle {
            height: 35
            width: 60
            color: "#c8955c"
            radius: 5
            Text {
                anchors.centerIn: parent
                text: ">"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i = viewNumber + 1;
                    if (i > 5)
                        viewNumber = 1;
                    else
                        viewNumber = i;
                }
            }
        }
    }
}
