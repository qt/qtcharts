// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

Item {
    id: main
    width: 400
    height: 320

    Column {
        id: column
        anchors.fill: parent
        anchors.bottomMargin: 10
        spacing: 0

        ChartViewSelector {
            id: chartViewSelector
            width: parent.width
            height: parent.height - customLegend.height - anchors.bottomMargin
            onSeriesAdded: customLegend.addSeries(seriesName, seriesColor);
        }

        CustomLegend {
            id: customLegend
            width: parent.width
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            onEntered: chartViewSelector.highlightSeries(seriesName);
            onExited: chartViewSelector.highlightSeries("");
            onSelected: chartViewSelector.selectSeries(seriesName);
        }
    }

    states: State {
        name: "highlighted"
        PropertyChanges {
            target: chartViewHighlighted
            width: column.width
            height: (column.height - column.anchors.margins * 2 - customLegend.height)
        }
        PropertyChanges {
            target: chartViewStacked
            width: 1
            height: 1
        }
    }
}
