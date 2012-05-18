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
            PieSlice { label: "Volkswagen"; value: 13.5 }
            PieSlice { label: "Toyota"; value: 10.9 }
            PieSlice { label: "Ford"; value: 8.6 }
            PieSlice { label: "Skoda"; value: 8.2 }
            PieSlice { label: "Volvo"; value: 6.8 }
        }

        // For dynamic data you can use the ChartModel API.
//        ChartModel {
//            id: chartModel
//            ChartModelRow { values: ["Volkswagen", 13.5] }
//            ChartModelRow { values: ["Toyota", 10.9] }
//            ChartModelRow { values: ["Ford", 8.6] }
//            ChartModelRow { values: ["Skoda", 8.2] }
//            ChartModelRow { values: ["Volvo", 6.8] }
//        }

        //  In this case you need to define how the data maps to pie slices with the ModelMapper API of the pie series.
//        PieSeries {
//            id: pieSeries
//            model: chartModel
//            modelMapper.mapLabels: 0
//            modelMapper.mapValues: 1
//            modelMapper.first: 0
//            modelMapper.count: -1 // "Undefined" = -1 by default
//            modelMapper.orientation: PieModelMapper.Vertical
//        }
    }

    Component.onCompleted: {
        // You can also add data dynamically
        pieSeries.model.append(["Others", 52.0]);
    }

    Timer {
        repeat: true
        interval: 2000
        running: true
        onTriggered: {
            // Set all slices as not exploded
            for (var i = 0; i < pieSeries.count; i++)
                pieSeries.slice(i).exploded = false;

            // Explode one of the slices
            __explodedIndex = (__explodedIndex + 1) % pieSeries.count;
            pieSeries.slice(__explodedIndex).exploded = true;
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
                    pieSeries.modelMapper.count = -1;
                    buttonText.text = "Hide others";
                } else {
                    pieSeries.modelMapper.count = 5;
                    buttonText.text = "Show others";
                    //pieModel.removeRow(pieModel.count - 1);
                    // TODO: removeAll("label") ?
                }
            }
        }
    }

    // TODO: show how to use data from a list model in a chart view
    // i.e. copy the data into a chart model
//    ListModel {
//        id: listModel
//        ListElement {
//            label: "Volkswagen"
//            value: 13.5
//        }
//        ListElement {
//            label: "Toyota"
//            value: 10.9
//        }
//        // and so on...
//    }

}
