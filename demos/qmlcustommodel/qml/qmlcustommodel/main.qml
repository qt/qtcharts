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
import QmlCustomModel 1.0

Rectangle {
    width: parent.width
    height: parent.height

    ChartView {
        id: chart
        title: "Custom model example"
        anchors.fill: parent
        theme: ChartView.ChartThemeLight

        // For dynamic data we use a custom data model derived from QAbstractiItemModel
        CustomModel {
            id: customModel
            CustomModelElement { values: ["Volkswagen", 13.5, 4.4] }
            CustomModelElement { values: ["Toyota", 10.9, 4.2] }
            CustomModelElement { values: ["Ford", 8.6, 3.0] }
            CustomModelElement { values: ["Skoda", 8.2, 1.9] }
            CustomModelElement { values: ["Volvo", 6.8, 1.5] }
        }

        LineSeries {
            name: "line"

            // TODO: the new mapper api
//            VXYModelMapper {
//                model: customModel
//                xColumn: 0
//                yColumn: 1
//            }
        }


        PieSeries {
            id: pieSeries
            size: 0.4
            horizontalPosition: 0.2
            verticalPosition: 0.3
        }

        VPieModelMapper {
            series: pieSeries
            model: customModel
            labelsColumn: 0
            valuesColumn: 1
        }

//        AreaSeries {
//            name: "area"
//            upperSeries: LineSeries {}
//            lowerSeries: LineSeries {}
//        }

//        BarSeries {
//            model: customModel
//            modelMapper.first: 0
//        }
    }


    // TODO: you could also implement appending to your model, for example:
//        pieSeries.model.append(["Others", 52.0]);

    // TODO: show how to use data from a list model in a chart view
    // i.e. copy the data into a custom model
//    ListModel {
//        id: listModel
//        ListElement {
//            label: "Volkswagen"
//            value: 13.5
//        }
//        ListElement {
//            label: "Toyota"
//            value: 10.9
//        }
//        // and so on...
//    }

}
