// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    id: main

    Column {
        id: column
        anchors.fill: parent
        anchors.bottomMargin: 10
        spacing: 0

        ChartViewSelector {
            id: chartViewSelector
            width: parent.width
            height: parent.height - customLegend.height - anchors.bottomMargin
            onSeriesAdded: (seriesName, seriesColor) => customLegend.addSeries(seriesName, seriesColor);
        }

        CustomLegend {
            id: customLegend
            width: parent.width
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            onEntered: seriesName => chartViewSelector.highlightSeries(seriesName);
            onExited: chartViewSelector.highlightSeries("");
            onSelected: seriesName => chartViewSelector.selectSeries(seriesName);
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
