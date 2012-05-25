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
    anchors.fill: parent
    property int __explodedIndex: -1
    property variant otherSlice: 0

    ChartView {
        id: chart
        title: "Top-5 car brand shares in Finland"
        anchors.top: parent.top
        anchors.bottom: button.top
        anchors.left: parent.left
        anchors.right: parent.right
        theme: ChartView.ChartThemeLight
        legend: ChartView.LegendBottom
        animationOptions: ChartView.SeriesAnimations

        // If you have static data, you can simply use the PieSlice API
        PieSeries {
            id: pieSeries
            PieSlice { id: volkswagenSlice; label: "Volkswagen"; value: 13.5 }
            PieSlice { label: "Toyota"; value: 10.9 }
            PieSlice { label: "Ford"; value: 8.6 }
            PieSlice { label: "Skoda"; value: 8.2 }
            PieSlice { label: "Volvo"; value: 6.8 }
        }
    }

    Component.onCompleted: {
        volkswagenSlice.exploded = true;
        // You can also add slices dynamically
        otherSlice = pieSeries.append("Others", 52.0);
    }

    Timer {
        repeat: true
        interval: 2000
        running: true
        onTriggered: {
            // Set all slices as not exploded
            for (var i = 0; i < pieSeries.count; i++)
                pieSeries.at(i).exploded = false;

            // Explode one of the slices
            __explodedIndex = (__explodedIndex + 1) % pieSeries.count;
            pieSeries.at(__explodedIndex).exploded = true;

            pieSeries.find("Volkswagen").exploded = true;
            // TODO: implement for convenience
//            pieSeries.removeAll("Ford");
        }
    }

    Rectangle {
        id: button
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        height: 40
        width: 100
        color: "orange"
        radius: 5
        Text {
            id: buttonText
            anchors.centerIn: parent
            text: "Hide others"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (buttonText.text == "Show others") {
                    buttonText.text = "Hide others";
                    // TODO: ?
                    otherSlice.visible = true;
                } else {
                    buttonText.text = "Show others";
                    otherSlice.visible = false;
                }
            }
        }
    }
}
