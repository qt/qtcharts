// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

//![1]
Item {
    id: main
    width: 600
    height: 400

    ControlPanel {
        id: controlPanel
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
//![1]

        onSignalSourceChanged: (source, signalCount, sampleCount) => {
            if (source == "sin")
                dataSource.generateData(0, signalCount, sampleCount);
            else
                dataSource.generateData(1, signalCount, sampleCount);
            scopeView.axisX().max = sampleCount;
        }
        onSeriesTypeChanged: type => scopeView.changeSeriesType(type);
        onRefreshRateChanged: rate => scopeView.changeRefreshRate(rate);
        onAntialiasingEnabled: enabled => scopeView.antialiasing = enabled;
        onOpenGlChanged: enabled => scopeView.openGL = enabled;
    }

//![2]
    ScopeView {
        id: scopeView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: controlPanel.right
        height: main.height
    }
//![2]

}
