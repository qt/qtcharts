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
    title: "line series"
    anchors.fill: parent

    property variant series: daSeries

    LineSeries {
        id: daSeries
        name: "line 1"
        onClicked: console.log("onClicked: " + point.x + ", " + point.y);
        XyPoint { x: 0; y: 0 }
        XyPoint { x: 1.1; y: 2.1 }
        XyPoint { x: 1.9; y: 3.3 }
        XyPoint { x: 2.1; y: 2.1 }
        XyPoint { x: 2.9; y: 4.9 }
        XyPoint { x: 3.4; y: 3.0 }
        XyPoint { x: 4.1; y: 3.3 }
    }

    LineSeries {
        name: "line 2"
        XyPoint { x: 1.1; y: 1.1 }
        XyPoint { x: 1.9; y: 2.3 }
        XyPoint { x: 2.1; y: 1.1 }
        XyPoint { x: 2.9; y: 3.9 }
        XyPoint { x: 3.4; y: 2.0 }
        XyPoint { x: 4.1; y: 2.3 }
    }
}
