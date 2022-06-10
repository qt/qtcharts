// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0

Rectangle {
    id: main
    width: 800
    height: 600
    property int viewCount: 9
    property variant colors: ["#637D74", "#403D3A", "#8C3B3B", "#AB6937", "#D4A960"]
    property int colorIndex: 0
    property int buttonWidth: 42

    function nextColor() {
        colorIndex++;
        return colors[colorIndex % colors.length];
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
            asynchronous: true
            onStatusChanged: {
                if (status == Loader.Ready && editorLoader.status == Loader.Ready && chartLoader.item) {
                    if (source.toString() === "Chart.qml")
                        editorLoader.item.chart = chartLoader.item.chart;
                    else
                        editorLoader.item.series = chartLoader.item.series;
                }
            }
        }

        Loader {
            id: editorLoader
            width: 280
            height: parent.height
            source: "ChartEditor.qml"
            asynchronous: true
            onStatusChanged: {
                if (status == Loader.Ready && chartLoader.status == Loader.Ready && chartLoader.item) {
                    if (source.toString() === "ChartEditor.qml")
                        editorLoader.item.chart = chartLoader.item.chart;
                    else
                        editorLoader.item.series = chartLoader.item.series;
                }
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
            text: "chart"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "Chart.qml";
                editorLoader.source = "ChartEditor.qml";
            }
        }
        Button {
            text: "pie"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "PieChart.qml";
                editorLoader.source = "PieEditor.qml";
            }
        }
        Button {
            text: "line"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "LineChart.qml";
                editorLoader.source = "LineEditor.qml";
            }
        }
        Button {
            text: "spline"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "SplineChart.qml";
                editorLoader.source = "LineEditor.qml";
            }
        }
        Button {
            text: "scatter"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "ScatterChart.qml";
                editorLoader.source = "ScatterEditor.qml";
            }
        }
        Button {
            text: "area"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "AreaChart.qml";
                editorLoader.source = "AreaEditor.qml";
            }
        }
        Button {
            text: "bar"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "BarChart.qml";
                editorLoader.source = "BarEditor.qml";
            }
        }
        Button {
            text: "sbar"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "StackedBarChart.qml";
                editorLoader.source = "BarEditor.qml";
            }
        }
        Button {
            text: "pbar"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "PercentBarChart.qml";
                editorLoader.source = "BarEditor.qml";
            }
        }
        Button {
            text: "hbar"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "HorizontalBarChart.qml";
                editorLoader.source = "BarEditor.qml";
            }
        }
        Button {
            text: "hsbar"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "HorizontalStackedBarChart.qml";
                editorLoader.source = "BarEditor.qml";
            }
        }
        Button {
            text: "hpbar"
            width: buttonWidth
            onClicked: {
                chartLoader.source = "HorizontalPercentBarChart.qml";
                editorLoader.source = "BarEditor.qml";
            }
        }
    }
}
