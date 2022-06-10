// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

Rectangle {
    id: legend
    color: "lightgray"

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

    Gradient {
        id: buttonGradient
        GradientStop { position: 0.0; color: "#F0F0F0" }
        GradientStop { position: 1.0; color: "#A0A0A0" }
    }

    Gradient {
        id: buttonGradientHovered
        GradientStop { position: 0.0; color: "#FFFFFF" }
        GradientStop { position: 1.0; color: "#B0B0B0" }
    }

    //![2]
    Component {
        id: legendDelegate
        Rectangle {
            id: rect
    //![2]
            property string name: seriesNames[index]
            property color markerColor: seriesColors[index]
            gradient: buttonGradient
            border.color: "#A0A0A0"
            border.width: 1
            radius: 4

            implicitWidth: label.implicitWidth + marker.implicitWidth + 30
            implicitHeight: label.implicitHeight + marker.implicitHeight + 10

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
                    opacity: 0.3
                    radius: 4
                    width: 12
                    height: 10
                }
                Text {
                    id: label
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: -1
                    text: name
                }
            }

    //![3]
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    rect.gradient = buttonGradientHovered;
                    legend.entered(label.text);
                }
                onExited: {
                    rect.gradient = buttonGradient;
                    legend.exited(label.text);
                    marker.opacity = 0.3;
                    marker.height = 10;
                }
                onClicked: {
                    legend.selected(label.text);
                    marker.opacity = 1.0;
                    marker.height = 12;
                }
            }
    //![3]
        }
    }

    //![1]
    Row {
        id: legendRow
        anchors.centerIn: parent
        spacing: 10

        Repeater {
            id: legendRepeater
            model: seriesCount
            delegate: legendDelegate
        }
    }
    //![1]
}
