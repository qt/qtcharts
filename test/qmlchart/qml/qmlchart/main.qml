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

    Chart {
        id: chart1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 2
        theme: Chart.ThemeIcy
//        opacity: 0.3

        Series {
            seriesType: Series.SeriesTypePie
        }

        // TODO: a bug: drawing order affects the drawing; if you draw chart1 first (by changing the
        // z-order), then chart2 is not shown at all. By drawing chart2 first, both are visible.
        // Also, if you don't draw line series on chart1 (only pie), both charts are visible.
//        Series {
//            seriesType: Series.SeriesTypeLine
//        }
        // TODO:
//        Series {
//            seriesType: Series.SeriesTypeBar
//        }
    }


    Chart {
        id: chart2
        anchors.top: chart1.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        theme: Chart.ThemeScientific

        ScatterSeries {
            data: [
                ScatterElement { x: 1.1; y: 2.1 },
                ScatterElement { x: 1.2; y: 2.0 },
                ScatterElement { x: 1.4; y: 2.3 }
            ]
        }
        ScatterSeries {
            data: [
                ScatterElement { x: 1.2; y: 2.2 },
                ScatterElement { x: 1.3; y: 2.2 },
                ScatterElement { x: 1.7; y: 2.6 }
            ]
        }
        ScatterSeries {
            data: [
                ScatterElement { x: 1.3; y: 2.3 },
                ScatterElement { x: 1.5; y: 2.4 },
                ScatterElement { x: 2.0; y: 2.9 }
            ]
        }
        ScatterSeries {
            data: [
                ScatterElement { x: 1.4; y: 2.4 },
                ScatterElement { x: 1.8; y: 2.7 },
                ScatterElement { x: 2.5; y: 3.2 }
            ]
        }
    }
}
