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
        id: chartView
        title: "Top-5 car brand shares in Finland"
        anchors.fill: parent
        theme: ChartView.ChartThemeLight
        axisX.max: 10
        axisX.min: 0
        axisY.max: 20
        axisY.min: 0
        animationOptions: ChartView.SeriesAnimations
        axisXLabels: [0, "2007", 1, "2008", 2, "2009", 3, "2010", 4, "2011", 5, "2012"]

        // For dynamic data we use a custom data model derived from QAbstractiItemModel
        CustomModel {
            id: customModel
            CustomModelElement { values: [0, "Manufacturer", 0, 1, 2, 3, 4] }
            CustomModelElement { values: [1, "Volkswagen", 10.3, 12.0, 12.8, 13.0, 13.8] }
            CustomModelElement { values: [2, "Toyota", 13.8, 13.5, 16.2, 13.7, 10.7] }
            CustomModelElement { values: [3, "Ford", 6.4, 7.1, 8.9, 8.2, 8.6] }
            CustomModelElement { values: [4, "Skoda", 4.7, 5.8, 6.9, 8.3, 8.2] }
            CustomModelElement { values: [5, "Volvo", 7.1, 6.7, 6.5, 6.3, 7.0] }
            CustomModelElement { values: [6, "Others", 57.7, 54.9, 48.7, 50.5, 51.7] }
        }

        BarSeries {
            name: "Others"
            barMargin: 0
            visible: false
            HBarModelMapper {
                model: customModel
                firstBarSetRow: 6
                lastBarSetRow: 6
                first: 2
            }
        }

        LineSeries {
            name: "Volkswagen"
            visible: false
            HXYModelMapper {
                model: customModel
                xRow: 0
                yRow: 1
                first: 2
            }
        }

        LineSeries {
            name: "Toyota"
            visible: false
            HXYModelMapper {
                model: customModel
                xRow: 0
                yRow: 2
                first: 2
            }
        }

        LineSeries {
            name: "Ford"
            visible: false
            HXYModelMapper {
                model: customModel
                xRow: 0
                yRow: 2
                first: 2
            }
        }

        LineSeries {
            name: "Skoda"
            visible: false
            HXYModelMapper {
                model: customModel
                xRow: 0
                yRow: 3
                first: 2
            }
        }

        LineSeries {
            name: "Volvo"
            visible: false
            HXYModelMapper {
                model: customModel
                xRow: 0
                yRow: 4
                first: 2
            }
        }

        PieSeries {
            id: pieSeries
            size: 0.4
            horizontalPosition: 0.7
            verticalPosition: 0.4
            onClicked: {
                // Show the selection by exploding the slice
                slice.exploded = !slice.exploded;

                // Update the line series to show the yearly data for this slice
                for (var i = 0; i < chartView.count; i++) {
                    if (chartView.series(i).name == slice.label) {
                        chartView.series(i).visible = slice.exploded;
                    }
                }
            }
        }

        VPieModelMapper {
            series: pieSeries
            model: customModel
            labelsColumn: 1
            valuesColumn: 2
            first: 1
        }
    }
}
