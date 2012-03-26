import QtQuick 1.0
import QtCommercial.Chart 1.0

Rectangle {
    width: parent.width
    height: parent.height

    // Another option for QML data api:
//    ListModel {
//        id: listModelForPie
//        // PieDataElement
//        ListElement {
//            label: "Apple"
//            value: 4.3
//        }
//        ListElement {
//            label: "Blackberry"
//            value: 15.1
//        }
//    }

    Component.onCompleted: {
        console.log("model: " + myModel);
//        console.log("model:" + myModel.item(0));
//        myModel.insert(1, {"time":1.4; "speed":41.1 });
//        scatter.appendData();
    }

    ListModel {
        ListElement {
            time: 0.0
            speed: 45.2
        }
    }
    ChartTableModel {
        id: myModel

//        ListElement {
//            time: 0.0
//            speed: 45.2
//        }
//        ListElement {
//            time: 0.5
//            speed: 48.9
//        }
//        ListElement {
//            time: 1.1
//            speed: 42.6
//        }

//        ChartTableElement {
//            time: 0.0
//            speed: 45.2
//        }
//        ChartTableElement {
//            time: 0.5
//            speed: 48.9
//        }
//        ChartTableElement {
//            time: 1.1
//            speed: 42.6
//        }
    }

    Chart {
        id: chart1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 2
        theme: Chart.ThemeBlueCerulean

//        BarSeries {
//        }

        ScatterSeries {
            model: myModel
//            xColumn: time
//            yColumn: speed
        }

//        PieSeries {
//            data: [
//                PieSlice { label: "Volkswagen"; value: 13.5 },
//                PieSlice { label: "Toyota"; value: 10.9 },
//                PieSlice { label: "Ford"; value: 8.6 },
//                PieSlice { label: "Skoda"; value: 8.2 },
//                PieSlice { label: "Volvo"; value: 6.8 },
//                PieSlice { label: "Others"; value: 52.0 }
//            ]
//        }
    }


    Chart {
        id: chart2
        anchors.top: chart1.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        theme: Chart.ThemeScientific

        LineSeries {
            data: [
                XyPoint { x: 0.0; y: 0.0 },
                XyPoint { x: 1.1; y: 2.1 },
                XyPoint { x: 2.9; y: 4.9 },
                XyPoint { x: 3.2; y: 3.0 }
            ]
        }

//        ScatterSeries {
//            id: scatter
//            data: [
//                XyPoint { x: 1.1; y: 1.1 },
//                XyPoint { x: 1.1; y: 1.2 },
//                XyPoint { x: 1.17; y: 1.15 }
//            ]
//        }
//        ScatterSeries {
//            data: [
//                XyPoint { x: 1.5; y: 1.5 },
//                XyPoint { x: 1.5; y: 1.6 },
//                XyPoint { x: 1.57; y: 1.55 }
//            ]
//        }
//        ScatterSeries {
//            data: [
//                XyPoint { x: 2.0; y: 2.0 },
//                XyPoint { x: 2.0; y: 2.1 },
//                XyPoint { x: 2.07; y: 2.05 }
//            ]
//        }
//        ScatterSeries {
//            data: [
//                XyPoint { x: 2.6; y: 2.6 },
//                XyPoint { x: 2.6; y: 2.7 },
//                XyPoint { x: 2.67; y: 2.65 }
//            ]
//        }
    }
}
