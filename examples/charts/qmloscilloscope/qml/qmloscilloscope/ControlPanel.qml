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

import QtQuick 2.1
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias openGLButton: openGLButton
    spacing: 8
    Layout.fillHeight: true
    signal animationsEnabled(bool enabled)
    signal seriesTypeChanged(string type)
    signal refreshRateChanged(variant rate);
    signal signalSourceChanged(string source, int signalCount, int sampleCount);
    signal antialiasingEnabled(bool enabled)
    signal openGlChanged(bool enabled)

    Text {
        text: "Scope"
        font.pointSize: 18
        color: "white"
    }

    MultiButton {
        id: openGLButton
        text: "OpenGL: "
        items: ["false", "true"]
        currentSelection: 0
        onSelectionChanged: openGlChanged(currentSelection == 1);
    }

    MultiButton {
        text: "Graph: "
        items: ["line", "spline", "scatter"]
        currentSelection: 0
        onSelectionChanged: seriesTypeChanged(items[currentSelection]);
    }

    MultiButton {
        id: signalSourceButton
        text: "Source: "
        items: ["sin", "linear"]
        currentSelection: 0
        onSelectionChanged: signalSourceChanged(
                                selection,
                                5,
                                sampleCountButton.items[sampleCountButton.currentSelection]);
    }

    MultiButton {
        id: sampleCountButton
        text: "Samples: "
        items: [6, 128, 1024, 10000]
        currentSelection: 2
        onSelectionChanged: signalSourceChanged(
                                signalSourceButton.items[signalSourceButton.currentSelection],
                                5,
                                selection);
    }

    MultiButton {
        text: "Refresh rate: "
        items: [1, 24, 60, 100]
        currentSelection: 2
        onSelectionChanged: refreshRateChanged(items[currentSelection]);
    }

    MultiButton {
        text: "Animations: "
        items: ["OFF", "ON"]
        currentSelection: 0
        onSelectionChanged: animationsEnabled(currentSelection == 1);
    }

    MultiButton {
        text: "Antialias: "
        items: ["OFF", "ON"]
        currentSelection: 0
        onSelectionChanged: antialiasingEnabled(currentSelection == 1);
    }
}
