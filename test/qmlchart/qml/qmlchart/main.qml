import QtQuick 1.0
import QtCommercial.Chart 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

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
