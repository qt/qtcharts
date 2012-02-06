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
