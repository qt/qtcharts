import QtQuick 1.0
import QtCommercial.Chart 1.0

Rectangle {
    width: 360
    height: 360

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

    // TODO: a bug: drawing order affects the drawing; if you draw chart1 first (by changing the
    // z-order), then chart2 is not shown at all. By drawing chart2 first, both are visible.
    Chart {
        id: chart2
        anchors.top: chart1.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        theme: Chart.ThemeScientific

        ScatterSeries {
            id: scatterSeries
            data: [
                ScatterElement { x: 1.1; y: 2.1 },
                ScatterElement { x: 1.2; y: 2.0 },
                ScatterElement { x: 1.4; y: 2.3 },
                ScatterElement { x: 3.1; y: 5.3 },
                ScatterElement { x: 4.1; y: 3.7 }
            ]
        }
    }

    Chart {
        id: chart1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 2
        theme: Chart.ThemeIcy
        opacity: 0.3

        Series {
            seriesType: Series.SeriesTypePie
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
