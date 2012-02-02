import QtQuick 1.0
import QtCommercial.Chart 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

//    Component.onCompleted: {
//        for (var i = 0.0; i < 100.0; i += 0.1) {
//            var x = i + Math.random() * 5;
//            var y = Math.abs(Math.sin(3.14159 / 50 * x) * 100) + (Math.random() * 5);
//            myData.append({'x':x, 'y':y});
//        }
//    }

//    ChartModel {
//        id: chartData
//        ChartElement {
//            y: 1.2
//        }
//        ChartElement {
//            x: 1.1
//            y: 1.2
//        }
//        ChartElement {
//            label: "February"
//            y: 1.2
//        }
//        ChartElement {
//            label: "January"
//            x: 0.2
//            y: 2.1
//        }
//    }

//    Series {
//        model: chartData
//        seriesType: pie
//        axis: Series.AxisSecondaryY
//    }

    ListModel {
        id: myData
        ListElement {
            nnn: 55.2
            mmm: 13.1
        }
        ListElement {
            nnn: 15.3
            mmm: 3.4
        }
    }

    Chart {
        anchors.fill: parent
        theme: Chart.ThemeIcy

        Series {
            seriesType: Series.SeriesTypePie
        }
        Series {
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
