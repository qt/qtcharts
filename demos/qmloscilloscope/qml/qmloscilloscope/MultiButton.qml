/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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
    id: button
    width: 115
    height: 31
    gradient: Gradient {
        GradientStop { position: mouseArea.pressed ? 1.0 : 0.0; color: "#A09090" }
        GradientStop { position: mouseArea.pressed ? 0.0 : 1.0; color: "#505050" }
    }
    smooth: true

    radius: 7
    property string text: "Option: "
    property variant items: ["first"]
    property int currentSelection: 0
    signal selectionChanged(variant selection)

    Text {
        id: buttonText
        anchors.centerIn: parent
        color: "#FFFFFF"
        text: button.text + button.items[currentSelection]
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            currentSelection = (currentSelection + 1) % items.length;
            selectionChanged(button.items[currentSelection]);
        }
    }
}
