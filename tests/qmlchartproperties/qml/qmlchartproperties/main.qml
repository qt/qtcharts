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
    id: main
    width: parent.width
    height: parent.height
    property int viewNumber: 0
    property int viewCount: 10
    property variant colors: ["#637D74", "#403D3A", "#8C3B3B", "#AB6937", "#D4A960"]
    property int colorIndex: 0

    function nextColor() {
        colorIndex++;
        console.log("color: " + colors[colorIndex % colors.length]);
        return colors[colorIndex % colors.length];
    }

    onViewNumberChanged: {
        if (viewNumber == 0) {
            chartLoader.source = "Chart.qml";
            editorLoader.source = "ChartEditor.qml";
        } else if (viewNumber == 1) {
            chartLoader.source = "PieChart.qml";
            editorLoader.source = "PieEditor.qml";
        } else if (viewNumber == 2) {
            chartLoader.source = "LineChart.qml";
            editorLoader.source = "LineEditor.qml";
        } else if (viewNumber == 3) {
            chartLoader.source = "SplineChart.qml";
            editorLoader.source = "LineEditor.qml";
        } else if (viewNumber == 4) {
            chartLoader.source = "ScatterChart.qml";
            editorLoader.source = "ScatterEditor.qml";
        } else if (viewNumber == 5) {
            chartLoader.source = "AreaChart.qml";
            editorLoader.source = "AreaEditor.qml";
        } else if (viewNumber == 6) {
            chartLoader.source = "BarChart.qml";
            editorLoader.source = "BarEditor.qml";
        } else if (viewNumber == 7) {
            chartLoader.source = "GroupedBarChart.qml";
            editorLoader.source = "BarEditor.qml";
        } else if (viewNumber == 8) {
            chartLoader.source = "StackedBarChart.qml";
            editorLoader.source = "BarEditor.qml";
        } else if (viewNumber == 9) {
            chartLoader.source = "PercentBarChart.qml";
            editorLoader.source = "BarEditor.qml";
        } else {
            console.log("Illegal view number");
        }
    }

    Row {
        anchors.top: parent.top
        anchors.bottom: buttonRow.top
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right

        Loader {
            id: chartLoader
            width: main.width - editorLoader.width
            height: parent.height
            source: "Chart.qml"
            onStatusChanged: {
                console.log("chartLoader.status: " + status + " " + source);
                if (status == Loader.Ready && editorLoader.status == Loader.Ready)
                    editorLoader.item.series = chartLoader.item.series;
            }
        }

        Loader {
            id: editorLoader
            width: 280
            height: parent.height
            source: "ChartEditor.qml"
            onStatusChanged: {
                console.log("editorLoader.status: " + status + " " + source);
                if (status == Loader.Ready && chartLoader.status == Loader.Ready)
                    editorLoader.item.series = chartLoader.item.series;
            }
        }
    }

    Row {
        id: buttonRow
        height: 40
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        Button {
            text: "previous"
            onClicked: {
                viewNumber = (viewNumber + viewCount - 1) % viewCount;
            }
        }

        Button {
            text: "next"
            onClicked: {
                viewNumber = (viewNumber + 1) % viewCount;
            }
        }
    }
}
