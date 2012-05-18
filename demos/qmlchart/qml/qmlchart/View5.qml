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
    anchors.fill: parent

    ChartView {
        title: "Bar series"
        anchors.fill: parent
        theme: ChartView.ChartThemeLight
        legend: ChartView.LegendBottom
//        axisXLabels: ["0", "2008", "1", "2009", "2", "2010", "3", "2012"]
        axisX.max: 10

        BarSeries {
            barCategories: [ "2008", "2009", "2010", "2011", "2012" ]
            model: barModel
        }

//        // TODO: optional syntax with ChartModel base model API
//        BarSeries {
//            model: chartModel
//            modelMapping: BarSeriesMapping {
//                // Giving "undefined" x mapping value means that the indexes are used as x-values
//                setIndexes: [BarSeriesMapping.Undefined, 0,
//                             BarSeriesMapping.Undefined, 1,
//                             BarSeriesMapping.Undefined, 2] // defaults to []
////                setValues: [
////                    BarSetMapping {x: BarSetMapping.Undefined; y: 0},
////                    BarSetMapping {x: BarSetMapping.Undefined; y: 1},
////                    BarSetMapping {x: BarSetMapping.Undefined; y: 2}
////                ]
//                orientation: BarSeriesMapping.Vertical // defaults to Vertical
//                startIndex: 0 // defaults to 0
//                count: BarSeriesMapping.Undefined // defaults to "Undefined"
//            }
//        }
    }

//    ChartModel {
//        id: chartModel
//    }

    BarModel {
        id: barModel
        BarSet { name: "Bob"; values: [2, 2, 3, 4, 5, 6] }
        BarSet { name: "Susan"; values: [5, 1, 2, 4, 1, 7] }
        BarSet { name: "James"; values: [3, 5, 8, 13, 5, 8] }
    }

    // TODO
//    Component.onCompleted: {
//        bobBars.append(1.2);
//        bobBars.append(1.5);
//        bobBars.append([1.5, 1.4, 1.9]);
//    }
}
