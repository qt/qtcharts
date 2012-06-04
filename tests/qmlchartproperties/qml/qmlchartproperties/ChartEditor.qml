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


Flow {
    id: flow
    spacing: 5
    flow: Flow.TopToBottom
    property variant series // TODO: rename to chart

    onSeriesChanged: {
        legendConnections.target = series.legend
    }

    Connections {
        target: series
        ignoreUnknownSignals: true
        onVisibleChanged:           console.log("chart.onVisibleChanged: " + series.visible);
        onThemeChanged:             console.log("chart.onThemeChanged: " + series.theme);
        onLegendChanged:            console.log("chart.onLegendChanged: " + series.legend);
        onAnimationOptionsChanged:  console.log("chart.onAnimationOptionsChanged: " + series.animationOptions);
        onTitleColorChanged:        console.log("chart.onTitleColorChanged: " + series.titleColor);
        onBackgroundColorChanged:   console.log("chart.onBackgroundColorChanged: " + series.backgroundColor);
    }

    Connections {
        id: legendConnections
        ignoreUnknownSignals: true
        onAlignmentChanged:         console.log("legend.onAlignmentChanged: " + series.legend.alignment);
        onVisibleChanged:           console.log("legend.onVisibleChanged: " + series.legend.visible);
    }

    Button {
        text: "visible"
        onClicked: series.visible = !series.visible;
    }
    Button {
        text: "theme +"
        onClicked: series.theme++;
    }
    Button {
        text: "theme -"
        onClicked: series.theme--;
    }
    Button {
        text: "legend top"
        onClicked: series.legend.alignment ^= Qt.AlignTop;
    }
    Button {
        text: "legend bottom"
        onClicked: series.legend.alignment ^= Qt.AlignBottom;
    }
    Button {
        text: "legend left"
        onClicked: series.legend.alignment ^= Qt.AlignLeft;
    }
    Button {
        text: "legend right"
        onClicked: series.legend.alignment ^= Qt.AlignRight;
    }
    Button {
        text: "legend visible"
        onClicked: series.legend.visible = !series.legend.visible;
    }
    Button {
        text: "animation opt +"
        onClicked: series.animationOptions++;
    }
    Button {
        text: "animation opt -"
        onClicked: series.animationOptions--;
    }
    Button {
        text: "title color"
        onClicked: series.titleColor = main.nextColor();
    }
    Button {
        text: "background color"
        onClicked: series.backgroundColor = main.nextColor();
    }
}
