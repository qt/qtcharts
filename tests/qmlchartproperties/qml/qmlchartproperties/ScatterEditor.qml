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
    property variant series

    onSeriesChanged: {
        seriesConnections.target = series;
    }

    Connections {
        id: seriesConnections
        ignoreUnknownSignals: true
        onNameChanged:              console.log("series.onNameChanged: " + series.name);
        onVisibleChanged:           console.log("series.onVisibleChanged: " + series.visible);
        onPointsVisibleChanged:     console.log("series.onPointsVisibleChanged: " + series.pointsVisible);
        onColorChanged:             console.log("series.onColorChanged: " + series.color);
        onBorderColorChanged:       console.log("series.onBorderColorChanged: " + series.borderColor);
        onCountChanged:             console.log("series.onCountChanged: " + series.count);
        onMarkerSizeChanged:        console.log("series.onMarkerSizeChanged: " + series.markerSize);
        onMarkerShapeChanged:       console.log("series.onMarkerShapeChanged: " + series.markerShape);
    }

    Button {
        text: "visible"
        onClicked: series.visible = !series.visible;
    }
    Button {
        text: "color"
        onClicked: series.color = main.nextColor();
    }
    Button {
        text: "borderColor"
        onClicked: series.borderColor = main.nextColor();
    }
    Button {
        text: "markerSize +"
        onClicked: series.markerSize += 1.0;
    }
    Button {
        text: "markerSize -"
        onClicked: series.markerSize -= 1.0;
    }
    Button {
        text: "markerShape"
        onClicked: series.markerShape = ((series.markerShape + 1) % 2);
    }
}
