/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
