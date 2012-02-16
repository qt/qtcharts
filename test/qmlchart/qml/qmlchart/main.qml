import QtQuick 1.0
import QtCommercial.Chart 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

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
//        console.log("Component.onCompleted: " + scatterElement.x);
//        console.log("Component.onCompleted: " + scatterElement.y);
//        console.log("Component.onCompleted: " + scatterElement.dataX);
//        console.log("Component.onCompleted: " + scatterElement.dataY);
        //console.log("Component.onCompleted: " + chartModel.get(0).x);
        //console.log("Component.onCompleted: " + chartModel.scatterElements);
//        console.log("Component.onCompleted: " + elementt.dataX);
//        console.log("Component.onCompleted: " + chartModel.get(0).dataX);
    }

    Chart {
        anchors.fill: parent
        theme: Chart.ThemeIcy

        ScatterSeries {
            id: scatterSeries
            data: [
                ScatterElement { x: 1.1; y: 2.1 },
                ScatterElement { x: 1.2; y: 2.0 },
                ScatterElement { x: 1.4; y: 2.3 },
                ScatterElement { x: 1.9; y: 2.5 },
                ScatterElement { x: 1.9; y: 3.4 },
                ScatterElement { x: 2.9; y: 1.4 },
                ScatterElement { x: 2.9; y: 2.4 },
                ScatterElement { x: 3.1; y: 5.3 },
                ScatterElement { x: 4.1; y: 3.7 }
            ]
            Component.onCompleted: {
                console.log("onCompleted " + data);
//                console.log("onCompleted " + data.get(0));
//                console.log("onCompleted " + data.get(0).x);
//                var element = {"x": 9.9, "y": 8.5};
//                data.append(element);
            }
        }

//        Series {
//            seriesType: Series.SeriesTypePie
//        }

//        Series {
//            seriesType: Series.SeriesTypeLine
//        }
        // TODO:
//        Series {
//            seriesType: Series.SeriesTypeBar
//        }
    }
}
