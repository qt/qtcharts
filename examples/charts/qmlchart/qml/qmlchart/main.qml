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

//![1]
import QtQuick 2.0
//![1]

Rectangle {
    width: 600
    height: 400
    property bool sourceLoaded: false

    ListView {
        id: root
        focus: true
        anchors.fill: parent
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 250
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds

        onCurrentIndexChanged: {
            if (infoText.opacity > 0.0) {
                if (sourceLoaded)
                    infoText.opacity = 0.0;
                else if (currentIndex != 0)
                    currentIndex = 0;
            }
        }

        model: ListModel {
            ListElement {component: "View1.qml"}
            ListElement {component: "View2.qml"}
            ListElement {component: "View3.qml"}
            ListElement {component: "View4.qml"}
            ListElement {component: "View5.qml"}
            ListElement {component: "View6.qml"}
            ListElement {component: "View7.qml"}
            ListElement {component: "View8.qml"}
            ListElement {component: "View9.qml"}
            ListElement {component: "View10.qml"}
            ListElement {component: "View11.qml"}
            ListElement {component: "View12.qml"}
        }

        delegate: Loader {
            width: root.width
            height: root.height

            source: component
            asynchronous: true

            onLoaded: sourceLoaded = true
        }
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
            text: "You can navigate between views using swipe or arrow keys"
        }

        Behavior on opacity {
            NumberAnimation { duration: 400 }
        }
    }
}
