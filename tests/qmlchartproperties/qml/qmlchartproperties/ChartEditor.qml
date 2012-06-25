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

Item {
    id: chartEditor
    property variant series // TODO: rename to chart
    onSeriesChanged: loader.item.chart = series;

    Flow {
        id: selectorFlow
        anchors.top: parent.top
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 5
        flow: Flow.TopToBottom

        Button {
            text: "Chart properties"
            unpressedColor: "#ff6138"
            onClicked: {
                loader.source = "ChartEditor1.qml";
                loader.item.chart = series;
            }
        }
        Button {
            text: "Legend properties"
            unpressedColor: "#79bd8f"
            onClicked: {
                loader.source = "ChartEditor2.qml";
                loader.item.chartLegend = series.legend;
            }
        }
        Button {
            text: "Axis X properties"
            unpressedColor: "#beeb9f"
            onClicked: {
                loader.source = "ChartEditor3.qml";
                loader.item.axis = series.axisX;
            }
        }
        Button {
            text: "Axis Y properties"
            unpressedColor: "#00a388"
            onClicked: {
                loader.source = "ChartEditor3.qml";
                loader.item.axis = series.axisY;
            }
        }
    }

    Loader {
        id: loader
        anchors.top: selectorFlow.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        source: "ChartEditor1.qml"
    }

}
