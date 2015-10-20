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
    id: main
    width: 500
    height: 400
    property string viewName: "DefaultAxes"

    Row {
        anchors.fill: parent
        anchors.topMargin: 10

        Loader {
            id: chartLoader
            width: parent.width - buttonColumn.width
            height: parent.height
            source: viewName + ".qml"
        }

        Column {
            id: buttonColumn
            width: 150
            height: parent.height
            spacing: 5

            Button {
                text: "Default axes"
                onClicked: viewName = "DefaultAxes";
            }
            Button {
                text: "Default axes reverted"
                onClicked: viewName = "DefaultAxesRevert";
            }
            Button {
                text: "User defined"
                onClicked: viewName = "UserDefined";
            }
            Button {
                text: "User defined reverted"
                onClicked: viewName = "UserDefinedRevert";
            }
            Button {
                text: "Chart axes"
                onClicked: viewName = "ChartAxes";
            }
            Button {
                text: "Chart axes reverted"
                onClicked: viewName = "ChartAxesRevert";
            }
            Button {
                text: "Configuring dynamically"
                onClicked: viewName = "ConfiguringDynamically";
            }
            Button {
                text: "Series specific dynamic"
                onClicked: viewName = "SeriesSpecificDynamic";
            }
            Button {
                text: "Creating dynamically"
                onClicked: viewName = "CreatingDynamically";
            }
            Button {
                text: "Switching dynamically"
                onClicked: viewName = "SwitchingDynamically";
            }
            Button {
                text: "Default + User defined"
                onClicked: viewName = "DefaultAndUserDefined";
            }
        }
    }
}
