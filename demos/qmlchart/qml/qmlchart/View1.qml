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

    ChartView {
        id: chart
        title: "Car brand shares in Finland"
        anchors.top: parent.top
        anchors.bottom: button.top
        anchors.left: parent.left
        anchors.right: parent.right
        theme: ChartView.ChartThemeLight
        legend: ChartView.LegendBottom
        animationOptions: ChartView.SeriesAnimations

        PieSeries {
            model: PieModel {
                id: pieModel
                PieSlice { label: "Volkswagen"; value: 13.5 }
                PieSlice { label: "Toyota"; value: 10.9 }
                PieSlice { label: "Ford"; value: 8.6 }
                PieSlice { label: "Skoda"; value: 8.2 }
                PieSlice { label: "Volvo"; value: 6.8 }
            }
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
            text: button.state == "" ? "Show others" : "Hide others"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (button.state == "") {
                    // The share of "others" was enabled -> append the data into the model
                    // TODO: this should also be doable by redefining the range inside the model
                    button.state = "show";
                    pieModel.append(["Others", 52.0]);
                } else {
                    // The share of "others" was disabled -> remove the data from the model
                    // TODO: this should also be doable by redefining the range inside the model
                    button.state = "";
                    pieModel.removeRow(pieModel.count - 1);
                }
            }
        }
    }


    // TODO: Optional syntax for defining models for different series. Is this really needed?
//    ChartModel {
//        id: chartModel
//        ChartElement { column1: "Volkswagen"; column2: 13.5; column3: 1.2 }
//        ChartElement { column1: "Toyota"; column2: 10.9; column3: 2.5 }
//    }
//    // column3 not used by pie series
//    PieSeries {
//        model: chartModel
//        mappings: [ {"column1":"label"}, {"column2":"value"} ]
//    }


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
