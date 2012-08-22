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

Rectangle {
    id: main
    width: 400
    height: 300
    property int viewNumber: 0

    Row {
        anchors.fill: parent
        anchors.topMargin: 10

        Loader {
            id: chartLoader
            width: parent.width - buttonColumn.width
            height: parent.height
            source: "Chart" + viewNumber + ".qml"
        }

        Column {
            id: buttonColumn
            width: 150
            height: parent.height
            spacing: 5

            Button {
                text: "Default"
                onClicked: viewNumber = 0;
            }
            Button {
                text: "User defined"
                onClicked: viewNumber = 1;
            }
            Button {
                text: "Chart axes"
                onClicked: viewNumber = 2;
            }
            Button {
                text: "Configuring dynamically"
                onClicked: viewNumber = 3;
            }
            Button {
                text: "Series specific dynamic"
                onClicked: viewNumber = 4;
            }
            Button {
                text: "Creating dynamically"
                onClicked: viewNumber = 5;
            }
            Button {
                text: "Switching dynamically"
                onClicked: viewNumber = 6;
            }
            Button {
                text: "Axis scale"
                onClicked: viewNumber = 7;
            }
            Button {
                text: "Legacy"
                onClicked: viewNumber = 8;
            }
        }
    }
}
