/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 1.0
import QtCommercial.Chart 1.1

Rectangle {
    id: chartViewSelector
    width: parent.width
    height: parent.height
    signal seriesAdded(string seriesName, color seriesColor)

    function highlightSeries(seriesName) {
        if (seriesName == "") {
            if (state != "")
                state = "";

            for (var i = 0; i < chartViewStacked.count; i++)
                chartViewStacked.series(i).opacity = 1.0;
        } else {
            var targetOpacity = 0.1;
            for (var j = 0; j < chartViewStacked.count; j++) {
                if (chartViewStacked.series(j).name != seriesName)
                    chartViewStacked.series(j).opacity = 0.25;
                else if (state == "highlight")
                    chartViewSelected.selectedSeries = chartViewStacked.series(j);
            }
        }
    }

    function selectSeries(seriesName) {
        for (var i = 0; i < chartViewStacked.count; i++) {
            if (chartViewStacked.series(i).name == seriesName) {
                chartViewSelected.selectedSeries = chartViewStacked.series(i);
                if (chartViewSelector.state == "")
                    chartViewSelector.state = "highlighted";
                else
                    chartViewSelector.state = "";
            }
        }
    }

    ChartViewStacked {
        id: chartViewStacked
        anchors.left: parent.left
        anchors.leftMargin: 0
        width: parent.width
        height: parent.height
        onSeriesAdded: chartViewSelector.seriesAdded(series.name, series.color);
    }

    ChartViewHighlighted {
        id: chartViewSelected
        anchors.left: chartViewStacked.right
        width: parent.width
        height: parent.height

        opacity: 0.0
        onClicked: {
            chartViewSelector.state = "";
        }
    }

    states: State {
        name: "highlighted"
        PropertyChanges {
            target: chartViewSelected
            opacity: 1.0
        }
        PropertyChanges {
            target: chartViewStacked
            anchors.leftMargin: -chartViewStacked.width
            opacity: 0.0
        }
    }

    transitions: Transition {
        PropertyAnimation {
            properties: "width, height, opacity, anchors.leftMargin"
            duration: 400
        }
    }
}
