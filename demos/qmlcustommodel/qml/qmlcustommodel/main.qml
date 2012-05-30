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
        axisX.max: 20
        axisY.max: 20

        // For dynamic data we use a custom data model derived from QAbstractiItemModel
        CustomModel {
            id: customModel
            CustomModelElement { values: [0, "Manufacturer", 1, 2] }
            CustomModelElement { values: [1, "Volkswagen", 13.5, 12.5] }
            CustomModelElement { values: [2, "Toyota", 10.9, 9.9] }
            CustomModelElement { values: [3, "Ford", 8.6, 7.6] }
            CustomModelElement { values: [4, "Skoda", 8.2, 7.2] }
            CustomModelElement { values: [5, "Volvo", 6.8, 5.8] }
        }

        LineSeries {
            name: "Volkswagen"
            HXYModelMapper {
                model: customModel
                xRow: 0
                yRow: 1
                first: 2
            }
        }

        LineSeries {
            name: "Toyota"
            HXYModelMapper {
                model: customModel
                xRow: 0
                yRow: 2
                first: 2
            }
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
            labelsColumn: 1
            valuesColumn: 2
            first: 1
        }

        AreaSeries {
            name: "Ford"
            upperSeries: LineSeries {
                HXYModelMapper {
                    model: customModel
                    xRow: 0
                    yRow: 3
                    first: 2
                }
            }
        }

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
