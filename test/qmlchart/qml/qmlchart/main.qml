import QtQuick 1.0
import QtCommercial.Chart 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

//    ListModel {
//        id: listModelForPie
//        // PieDataElement
//        ListElement {
//            label: "Apple"
//            value: 40.3
//        }
//        ListElement {
//            label: "Pumpkin"
//            value: 10.1
//        }
//        ListElement {
//            label: "Raspberry"
//            value: 15.1
//        }
//        ListElement {
//            label: "Strawberry"
//            value: 29.9
//        }
//    }

//    ChartModel {
//        id: chartModel
//        ListElement {
//            label: "dada"
//            x: 1.1
//            y: 3.2
//        }
//    }

//    ChartModel {
//        ScatterElement {x: 1.1; y: 1.2}
//        ScatterElement {x: 1.3; y: 1.9}
//        ScatterElement {x: 1.1; y: 1.2}
//    }

    ListModel {
        id: listModelScatter
        ListElement {
            height: 154
            weight: 54
        }
        ListElement {
            height: 166
            weight: 64
        }
        ListElement {
            height: 199
            weight: 97
        }
    }

//    Chart {
//        anchors.fill: parent
//        theme: Chart.ThemeIcy
//        ScatterSeries {
//            model: listModelScatter
//            name: "scatter"
//            xValue: x
//            yValue: y
//        }
//    }

    Chart {
        anchors.fill: parent
        theme: Chart.ThemeIcy

//        PieSeries {
//            labels: ["point1", "point2", "point3", "point4", "point5"]
//            datax: [2, 1.5, 3, 3, 3]
//        }
//        PieSeries {
//            name: "raspberry pie"
//            seriesLabels: ["point1", "point2", "point3", "point4", "point5"]
//            seriesData: [2, 1.5, 3, 3, 3]
//        }
//        ScatterSeries {
//            name: "scatter1"
//            datax: [2, 1.5, 3, 3, 3]
//            datay: [2, 1.5, 3, 3, 3]
//        }
//        Series {
//            labels: ["point1", "point2", "point3", "point4", "point5"]
//            datax: [2, 1.5, 3, 3, 3]
//            seriesType: Series.SeriesTypePie
//        }
        Series {
            seriesType: Series.SeriesTypePie
            //model: listModelForPie
            //seriesData: {11.0, 6.4, 12.6, 22.4}
            //seriesLabels: {"Strawberry", "Blackberry", "Apple", "Pumpkin"}
        }

        Series {
//            data: {[1.2], "y":2.2 }
            seriesType: Series.SeriesTypeScatter
        }
        Series {
            seriesType: Series.SeriesTypeLine
        }
        // TODO:
//        Series {
//            seriesType: Series.SeriesTypeBar
//        }
    }
}
