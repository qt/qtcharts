/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

Rectangle {
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
