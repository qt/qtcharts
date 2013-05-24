/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

//![1]
import QtQuick 1.0
import QtCommercial.Chart 1.1

ChartView {
    title: "Box Plot series"
    width: 400
    height: 300
    theme: ChartView.ChartThemeBrownSand
    legend.alignment: Qt.AlignBottom

//![1]
//![2]
    BoxPlotSeries {
        id: plotSeries
        name: "Income"
        //axisX: BarCategoryAxis { categories: ["Jan", "Feb", "Mar", "Apr", "May"] }
        BoxSet { values: [3, 4, 4.4, 6, 7] }
        BoxSet { label: "Tok"; values: [5, 6, 7.5, 8, 12] }
        BoxSet { label: "Kol"; values: [2, 5, 5.7, 8, 9] }
        BoxSet { id: nelBox
                 label: "Nel"
                 values: [5, 6, 6.8, 7, 8];
                 onColorChanged: {
                    console.log("onColorChanged")
                 }
        }
        BoxSet { label: "Vii"; values: [4, 5, 5.2, 6, 7]; color: "#aa0000" }
        //onClicked: console.log("series onClicked " + boxset.median)
        //onHovered: console.log("series onHovered " + status + "median = " + boxset.median)
        onCountChanged: console.log("onCountChanged")
    }
//![2]

    Rectangle {
        id: moreButton
        width: 50
        height: 50
        color: "gray"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                nelBox.color = "#0000aa"
                var com = Qt.createComponent("box.qml")
                if (com.status == Component.Ready) {
                    var obj = com.createObject(moreButton)
                    obj.lowerExtreme = 1.2
                    console.log("lowerExtreme = " + obj.lowerExtreme)
                    obj.lowerQuartile = 2.2
                    console.log("lowerQuartile = " + obj.lowerQuartile)
                    obj.median = 3.2
                    console.log("median = " + obj.median)
                    obj.upperQuartile = 4.2
                    console.log("upperQuartile = " + obj.upperQuartile)
                    obj.upperExtreme = 5.2
                    console.log("upperExtreme = " + obj.upperExtreme)
                    obj.label = "mik"
                    console.log("label = " + obj.label)
                    plotSeries.append(obj)
                    obj.color = "#aa0000"
                    console.log("color = " + obj.color)
                    obj.borderColor = "#00aa00"
                } else {
                    console.log(com.errorString())
                }
            }
        }
    }

//![3]
}
//![3]
