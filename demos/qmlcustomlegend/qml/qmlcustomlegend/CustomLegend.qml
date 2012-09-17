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
import QtCommercial.Chart 1.1

Rectangle {
    id: legend
    radius: 8
    color: "lightblue"
    property int seriesCount: 0
    property variant seriesNames: []
    property variant seriesColors: []
    signal entered(string seriesName)
    signal exited(string seriesName)
    signal selected(string seriesName)

    function addSeries(seriesName, color) {
        var names = seriesNames;
        names[seriesCount] = seriesName;
        seriesNames = names;

        var colors = seriesColors;
        colors[seriesCount] = color;
        seriesColors = colors;

        seriesCount++;
    }

    //![2]
    Component {
        id: legendDelegate
        Rectangle {
            id: rect
        // ...
    //![2]
            property string name: seriesNames[index]
            property color markerColor: seriesColors[index]
            color: "transparent"
            border.color: seriesColors[index]
            border.width: 2
            radius: 4
            height: 20
            width: row.width + row.anchors.leftMargin * 2

            Row {
                id: row
                spacing: 5
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                Rectangle {
                    id: marker
                    anchors.verticalCenter: parent.verticalCenter
                    color: markerColor
                    radius: 4
                    width: 12
                    height: 12
                }
                Text {
                    id: label
                    anchors.verticalCenter: parent.verticalCenter
                    text: name
                }
            }

    //![3]
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    rect.color = "white";
                    legend.entered(label.text);
                }
                onExited: {
                    rect.color = "transparent";
                    legend.exited(label.text);
                }
                onClicked: {
                    legend.selected(label.text);
                }
            }
    //![3]
        }
    }

    //![1]
    Row {
        id: legendRow
        anchors.centerIn: parent
        spacing: 4

        Repeater {
            id: legendRepeater
            model: seriesCount
            delegate: legendDelegate
        }
    }
    //![1]
}
