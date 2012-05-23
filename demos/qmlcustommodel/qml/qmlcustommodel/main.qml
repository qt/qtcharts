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

    ChartView {
        id: chart
        title: "Custom model example"
        anchors.fill: parent
        theme: ChartView.ChartThemeLight

        // For dynamic data you can use the ChartModel API.
        ChartModel {
            id: chartModel
            ChartModelElement { values: [0, "Volkswagen", 13.5, 4.4] }
            ChartModelElement { values: [0, "Toyota", 10.9, 4.2] }
            ChartModelElement { values: [0, "Ford", 8.6, 3.0] }
            ChartModelElement { values: [0, "Skoda", 8.2, 1.9] }
            ChartModelElement { values: [0, "Volvo", 6.8, 1.5] }
        }

        LineSeries {
            name: "line"
            // TODO: the current mapper api
            model: chartModel
            modelMapper.mapX: 3
            modelMapper.mapY: 3

            // TODO: the new mapper api
//            XYModelMapperVertical {
//                model: chartModel
//                xColumn: 0
//                yColumn: 1
//            }
        }


        PieSeries {
            id: pieSeries
            size: 0.4
            horizontalPosition: 0.2
            verticalPosition: 0.3

//            model: chartModel
//            // TODO: the current mapper api
//            modelMapper.mapLabels: 1
//            modelMapper.mapValues: 2
//            modelMapper.first: 0
//            modelMapper.count: -1 // "Undefined" = -1 by default
//            modelMapper.orientation: PieModelMapper.Vertical

            // TODO: the new mapper api
//            PieModelMapperVertical {
//                model: chartModel
//                labelsColumn: 0
//                valuesColumn: 1
//            }
        }

        // TODO: the new mapper api
//        PieModelMapperVertical {
//            series: pieSeries
//            model: chartModel
//            labelsColumn: 0
//            valuesColumn: 1
//        }

        AreaSeries {
            name: "area"
            upperSeries: LineSeries {
                model: chartModel
                modelMapper.mapX: 2
                modelMapper.mapY: 2
            }
            lowerSeries: LineSeries {
                model: chartModel
                modelMapper.mapX: 2
                modelMapper.mapY: 0
            }
        }

        // TODO: BarSeries with ChartModel base model API
//        BarSeries {
//            model: chartModel
//            modelMapper.first: 0
//        }
    }


    // TODO: you could also implement appending to your model, for example:
//        pieSeries.model.append(["Others", 52.0]);

    // TODO: show how to use data from a list model in a chart view
    // i.e. copy the data into a chart model
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
