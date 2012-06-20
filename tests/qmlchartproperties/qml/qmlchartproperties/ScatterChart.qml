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
    title: "scatter series"
    axisX.max: 4
    axisY.max: 4
    property variant series: scatterSeries

    ScatterSeries {
        id: scatterSeries
        name: "scatter 1"
        XyPoint { x: 1.5; y: 1.5 }
        XyPoint { x: 1.5; y: 1.6 }
        XyPoint { x: 1.57; y: 1.55 }
        XyPoint { x: 1.8; y: 1.8 }
        XyPoint { x: 1.9; y: 1.6 }
        XyPoint { x: 2.1; y: 1.3 }
        XyPoint { x: 2.5; y: 2.1 }

        onNameChanged:              console.log("scatterSeries.onNameChanged: " + name);
        onVisibleChanged:           console.log("scatterSeries.onVisibleChanged: " + visible);
        onColorChanged:             console.log("scatterSeries.onColorChanged: " + color);
        onBorderColorChanged:       console.log("scatterSeries.onBorderColorChanged: " + borderColor);
        onCountChanged:             console.log("scatterSeries.onCountChanged: " + count);
    }

    ScatterSeries {
        name: "scatter2"
        XyPoint { x: 2.0; y: 2.0 }
        XyPoint { x: 2.0; y: 2.1 }
        XyPoint { x: 2.07; y: 2.05 }
        XyPoint { x: 2.2; y: 2.9 }
        XyPoint { x: 2.4; y: 2.7 }
        XyPoint { x: 2.67; y: 2.65 }
    }
}
