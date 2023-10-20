// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Rectangle {
    id: root
    width: 1200
    height: 600

    color: "#f0f0f0"

    property bool isHorizontalView: root.width >= root.height

    Item {
        anchors.fill: parent
        anchors.margins: 8

        Rectangle {
            id: listRect
            width: isHorizontalView ? 200 : parent.width
            height: isHorizontalView ? parent.height : parent.height / 3
            x: 0
            y: isHorizontalView ? 0 : parent.height - height
            border.width: 1

            ListView {
                id: listView
                focus: true
                anchors.fill: parent
                anchors.margins: 1
                highlightMoveDuration: 250
                highlightResizeDuration: 0
                orientation: ListView.Vertical
                boundsBehavior: Flickable.StopAtBounds
                currentIndex: 0
                clip: true

                model: ListModel {
                    ListElement {
                        name: "Area Chart"
                        component: "AreaSeries.qml"
                    }
                    ListElement {
                        name: "Bar Chart"
                        component: "BarSeries.qml"
                    }
                    ListElement {
                        name: "Bar Chart Horizontal"
                        component: "BarSeriesHorizontal.qml"
                    }
                    ListElement {
                        name: "Bar Chart Percent"
                        component: "BarSeriesPercent.qml"
                    }
                    ListElement {
                        name: "Bar Chart Percent Horizontal"
                        component: "BarSeriesPercentHorizontal.qml"
                    }
                    ListElement {
                        name: "Bar Chart Stacked"
                        component: "BarSeriesStacked.qml"
                    }
                    ListElement {
                        name: "Bar Chart Stacked Horizontal"
                        component: "BarSeriesStackedHorizontal.qml"
                    }
                    ListElement {
                        name: "Box Plot Chart"
                        component: "BoxPlotSeries.qml"
                    }
                    ListElement {
                        name: "Candlestick Chart"
                        component: "CandlestickSeries.qml"
                    }
                    ListElement {
                        name: "Category Axis"
                        component: "CategoryAxis.qml"
                    }
                    ListElement {
                        name: "Category Axis Polar"
                        component: "CategoryAxisPolar.qml"
                    }
                    ListElement {
                        name: "Custom Legend"
                        component: "customlegend/Main.qml"
                    }
                    ListElement {
                        name: "Datetime Axis"
                        component: "DateTimeAxis.qml"
                    }
                    ListElement {
                        name: "Datetime Axis Polar"
                        component: "DateTimeAxisPolar.qml"
                    }
                    ListElement {
                        name: "Donut"
                        component: "Donut.qml"
                    }
                    ListElement {
                        name: "F1 Legends"
                        component: "f1legends/F1Legends.qml"
                    }
                    ListElement {
                        name: "Line Chart"
                        component: "LineSeries.qml"
                    }
                    ListElement {
                        name: "Pie Chart"
                        component: "PieChart.qml"
                    }
                    ListElement {
                        name: "Spline Chart"
                        component: "SplineSeries.qml"
                    }
                    ListElement {
                        name: "Scatter Chart"
                        component: "ScatterSeries.qml"
                    }
                    ListElement {
                        name: "Two Series in Chart"
                        component: "TwoSeries.qml"
                    }
                    ListElement {
                        name: "Two Series in Polar Chart"
                        component: "TwoSeriesPolar.qml"
                    }
                    ListElement {
                        name: "Wheel of Fortune"
                        component: "WheelOfFortune.qml"
                    }
                }

                delegate: Text {
                    property string source: component
                    text: name
                    width: listView.width
                    leftPadding: 4

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            listView.currentIndex = index
                        }
                    }
                }

                highlight: Rectangle {
                    color: "lightblue";
                }
            }
        }

        Rectangle {
            width: isHorizontalView ? parent.width - listView.width - 8 : parent.width
            height: isHorizontalView ? parent.height : parent.height - listView.height - 8
            radius: 5
            x: isHorizontalView ? 208 : 0
            y: 0
            clip: true

            Loader {
                anchors.fill: parent
                asynchronous: true
                source: listView.currentItem.source
            }
        }
    }
}
