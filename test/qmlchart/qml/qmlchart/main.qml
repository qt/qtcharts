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
//        console.log("Component.onCompleted: " + ChartPointElement.x);
//        console.log("Component.onCompleted: " + ChartPointElement.y);
//        console.log("Component.onCompleted: " + ChartPointElement.dataX);
//        console.log("Component.onCompleted: " + ChartPointElement.dataY);
        //console.log("Component.onCompleted: " + chartModel.get(0).x);
        //console.log("Component.onCompleted: " + chartModel.ChartPointElements);
//        console.log("Component.onCompleted: " + elementt.dataX);
//        console.log("Component.onCompleted: " + chartModel.get(0).dataX);
        //ChartPointElement { x: 0.3; y: 0.3 }
    }

    Chart {
        id: chart1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 2
        theme: Chart.ThemeVanilla

        PieSeries {
            data: [
                // TODO: "NnElement" matches the naming convention of for example ListModel...
                // But PieSlice would match the naming of QtCommercial Charts C++ api
                ChartPieElement { label: "Volkswagen"; value: 13.5 },
                ChartPieElement { label: "Toyota"; value: 10.9 },
                ChartPieElement { label: "Ford"; value: 8.6 },
                ChartPieElement { label: "Skoda"; value: 8.2 },
                ChartPieElement { label: "Volvo"; value: 6.8 },
                ChartPieElement { label: "Others"; value: 52.0 }
            ]
        }

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

        LineSeries {
            data: [
                ChartPointElement { x: 0.0; y: 0.0 },
                ChartPointElement { x: 1.1; y: 2.1 },
                ChartPointElement { x: 2.9; y: 4.9 },
                ChartPointElement { x: 3.2; y: 3.0 }
            ]
        }

        ScatterSeries {
            data: [
                ChartPointElement { x: 1.1; y: 1.1 },
                ChartPointElement { x: 1.1; y: 1.2 },
                ChartPointElement { x: 1.17; y: 1.15 }
            ]
        }
        ScatterSeries {
            data: [
                ChartPointElement { x: 1.5; y: 1.5 },
                ChartPointElement { x: 1.5; y: 1.6 },
                ChartPointElement { x: 1.57; y: 1.55 }
            ]
        }
        ScatterSeries {
            data: [
                ChartPointElement { x: 2.0; y: 2.0 },
                ChartPointElement { x: 2.0; y: 2.1 },
                ChartPointElement { x: 2.07; y: 2.05 }
            ]
        }
        ScatterSeries {
            id: scatter4
            data: [
                ChartPointElement { x: 2.6; y: 2.6 },
                ChartPointElement { x: 2.6; y: 2.7 },
                ChartPointElement { x: 2.67; y: 2.65 }
            ]
        }
    }
}
