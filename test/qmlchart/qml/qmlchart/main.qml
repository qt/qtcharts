/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

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
//        console.log("model:" + myModel.item(0));
//        myModel.insert(1, {"time":1.4; "speed":41.1 });
//        scatter.appendData();
//        chart1.theme = Chart.ThemeHighContrast;
//        chart2.theme = Chart.ThemeHighContrast;
    }


    Chart {
        id: chart1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 2
        theme: Chart.ThemeBlueCerulean

        BarSeries {
            barCategories: [ "2008", "2009", "2010", "2011", "2012" ]
        }

        PieSeries {
            slices: [
                PieSlice { label: "Volkswagen"; value: 13.5 },
                PieSlice { label: "Toyota"; value: 10.9 },
                PieSlice { label: "Ford"; value: 8.6 },
                PieSlice { label: "Skoda"; value: 8.2 },
                PieSlice { label: "Volvo"; value: 6.8 },
                PieSlice { label: "Others"; value: 52.0 }
            ]
        }
    }


    Chart {
        id: chart2
        anchors.top: chart1.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        theme: Chart.ThemeBrownSand

        LineSeries {
            points: [
                XyPoint { x: 0.0; y: 0.0 },
                XyPoint { x: 1.1; y: 2.1 },
                XyPoint { x: 2.9; y: 4.9 },
                XyPoint { x: 3.2; y: 3.0 }
            ]
        }

        SplineSeries {
            points: [
                XyPoint { x: 0.0; y: 0.3 },
                XyPoint { x: 1.1; y: 3.2 },
                XyPoint { x: 4.17; y: 3.15 }
            ]
        }

        ScatterSeries {
            points: [
                XyPoint { x: 1.5; y: 1.5 },
                XyPoint { x: 1.5; y: 1.6 },
                XyPoint { x: 1.57; y: 1.55 }
            ]
        }
        ScatterSeries {
            points: [
                XyPoint { x: 2.0; y: 2.0 },
                XyPoint { x: 2.0; y: 2.1 },
                XyPoint { x: 2.07; y: 2.05 }
            ]
        }
        ScatterSeries {
            points: [
                XyPoint { x: 2.6; y: 2.6 },
                XyPoint { x: 2.6; y: 2.7 },
                XyPoint { x: 2.67; y: 2.65 }
            ]
        }
    }
}
