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

Rectangle {
    anchors.fill: parent

    Chart {
        anchors.fill: parent
        theme: Chart.ChartThemeHighContrast

        AreaSeries {
            name: "Area"
            points: [
                XyPoint { x: 0.0; y: 1.1 },
                XyPoint { x: 2.5; y: 3.6 },
                XyPoint { x: 3.57; y: 2.55 }
            ]
            lowerPoints: [
                XyPoint { x: 0.0; y: 0.0 },
                XyPoint { x: 2.5; y: 0.0 },
                XyPoint { x: 3.57; y: 0.0 }
            ]
        }

        ScatterSeries {
            name: "Scatter1"
            points: [
                XyPoint { x: 1.5; y: 1.5 },
                XyPoint { x: 1.5; y: 1.6 },
                XyPoint { x: 1.57; y: 1.55 }
            ]
        }
        ScatterSeries {
            name: "Scatter2"
            points: [
                XyPoint { x: 2.0; y: 2.0 },
                XyPoint { x: 2.0; y: 2.1 },
                XyPoint { x: 2.07; y: 2.05 }
            ]
        }
        ScatterSeries {
            name: "Scatter3"
            points: [
                XyPoint { x: 2.6; y: 2.6 },
                XyPoint { x: 2.6; y: 2.7 },
                XyPoint { x: 2.67; y: 2.65 }
            ]
        }
    }
}
