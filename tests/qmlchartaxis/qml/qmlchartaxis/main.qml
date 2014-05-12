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
    id: main
    width: 400
    height: 300
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
            Button {
                text: "Legacy"
                onClicked: viewName = "Legacy";
            }
        }
    }
}
