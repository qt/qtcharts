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
        anchors.fill: parent
        theme: Chart.ChartThemeDark

        BarSeries {
            barCategories: [ "2008", "2009", "2010", "2011", "2012" ]
            // TBD: data
        }

        PieSeries {
            horizontalPosition: 0.2
            verticalPosition: 0.3
            size: 0.4
            endAngle: 0.52 * 360 // The share of "others" is 52%
            slices: [
                PieSlice { label: "Volkswagen"; value: 13.5 },
                PieSlice { label: "Toyota"; value: 10.9 },
                PieSlice { label: "Ford"; value: 8.6 },
                PieSlice { label: "Skoda"; value: 8.2 },
                PieSlice { label: "Volvo"; value: 6.8 }
            ]
        }
    }
}
