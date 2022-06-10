// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0

Item {
    width: 600
    height: 400
    property bool sourceLoaded: false
    property alias currentIndex: root.currentIndex
    property alias info: infoText

    ListView {
        id: root
        focus: true
        anchors.fill: parent
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 250
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds

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
    }
}
