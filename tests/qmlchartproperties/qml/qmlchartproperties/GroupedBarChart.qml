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

ChartView {
    title: "Grouped bar series"
    anchors.fill: parent
    theme: ChartView.ChartThemeLight
    legend.alignment: Qt.AlignBottom
    axisXLabels: ["0", "2007", "1", "2008", "2", "2009", "3", "2010", "4", "2011", "5", "2012"]

    property variant series: barSeries

    GroupedBarSeries {
        id: barSeries
        name: "bar"
        BarSet { label: "Bob"; values: [2, 2, 3, 4, 5, 6]
            onClicked:                  console.log("barset.onClicked: " + index);
            onHovered:                  console.log("barset.onHovered: " + status);
            onColorChanged:             console.log("barset.onColorChanged: " + color);
            onBorderColorChanged:       console.log("barset.onBorderColorChanged: " + color);
            onLabelColorChanged:        console.log("barset.onLabelColorChanged: " + color);
            onCountChanged:             console.log("barset.onCountChanged: " + count);
        }
        BarSet { label: "Susan"; values: [5, 1, 2, 4, 1, 7] }
        BarSet { label: "James"; values: [3, 5, 8, 13, 5, 8] }

        onNameChanged:              console.log("groupedBarSeries.onNameChanged: " + series.name);
        onVisibleChanged:           console.log("groupedBarSeries.onVisibleChanged: " + series.visible);
        onClicked:                  console.log("groupedBarSeries.onClicked: " + barset + " " + index);
        onHovered:                  console.log("groupedBarSeries.onHovered: " + barset + " " + status);
        onLabelsVisibleChanged:     console.log("groupedBarSeries.onLabelsVisibleChanged: " + series.labelsVisible);
        onCountChanged:             console.log("groupedBarSeries.onCountChanged: " + count);
    }
}
