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

Item {
    id: chartEditor
    property variant series // TODO: rename to chart
    onSeriesChanged: {
        if (loader.item != undefined)
            loader.item.chart = series;
    }

    function selectButton(button) {
        chartButton.color = "#79bd8f";
        titleButton.color = "#79bd8f";
        legendButton.color = "#79bd8f";
        axisXButton.color = "#79bd8f";
        axisYButton.color = "#79bd8f";
        button.color = "#00a388";
    }

    Flow {
        id: selectorFlow
        anchors.top: parent.top
        height: 90
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 5
        flow: Flow.TopToBottom

        Button {
            id: chartButton
            text: "Chart properties"
            unpressedColor: "#79bd8f"
            onClicked: {
                selectButton(chartButton);
                loader.source = "ChartEditorProperties.qml";
                loader.item.chart = series;
            }
        }
        Button {
            id: titleButton
            text: "Title properties"
            unpressedColor: "#79bd8f"
            onClicked: {
                selectButton(titleButton);
                loader.source = "ChartEditorTitle.qml";
                loader.item.chart = series;
            }
        }
        Button {
            id: legendButton
            text: "Legend properties"
            unpressedColor: "#79bd8f"
            onClicked: {
                selectButton(legendButton);
                loader.source = "ChartEditorLegend.qml";
                loader.item.chartLegend = series.legend;
            }
        }
        Button {
            id: axisXButton
            text: "Axis X properties"
            unpressedColor: "#79bd8f"
            onClicked: {
                selectButton(axisXButton);
                loader.source = "ChartEditorAxis.qml";
                loader.item.axis = series.axisX;
            }
        }
        Button {
            id: axisYButton
            text: "Axis Y properties"
            unpressedColor: "#79bd8f"
            onClicked: {
                selectButton(axisYButton);
                loader.source = "ChartEditorAxis.qml";
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
    }
}
