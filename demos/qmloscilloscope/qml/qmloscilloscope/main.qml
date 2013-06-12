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

//![1]
Rectangle {
    id: main
    width: 400
    height: 300
    color: "#404040"

    ControlPanel {
        id: controlPanel
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
// ...
//![1]

        onSignalSourceChanged: {
            if (source == "sin")
                dataSource.generateData(0, signalCount, sampleCount);
            else
                dataSource.generateData(1, signalCount, sampleCount);
        }
        onAnimationsEnabled: scopeView.setAnimations(enabled);
        onSeriesTypeChanged: scopeView.changeSeriesType(type);
        onRefreshRateChanged: scopeView.changeRefreshRate(rate);
        onAntialiasingEnabled: dataSource.setAntialiasing(enabled);
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
