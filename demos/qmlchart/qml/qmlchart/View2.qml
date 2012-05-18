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

    ChartView {
        title: "Line&Spline"
        anchors.fill: parent
        theme: ChartView.ChartThemeBrownSand
        animationOptions: ChartView.NoAnimation

        LineSeries {
            name: "Line"
            model: chartModel
            modelMapper.mapX: 0
            modelMapper.mapY: 1
            modelMapper.first: 0
            modelMapper.count: -1
            modelMapper.orientation: XYModelMapper.Vertical
        }

        SplineSeries {
            name: "Spline"
            model: chartModel
            modelMapper.mapX: 0
            modelMapper.mapY: 2
        }
    }

    ChartModel {
        id: chartModel
        ChartModelElement { values: [0.0, 0.0, 0.3] }
        ChartModelElement { values: [1.1, 2.1, 3.2] }
        ChartModelElement { values: [1.9, 3.3, 2.4] }
        ChartModelElement { values: [2.1, 2.1, 2.1] }
        ChartModelElement { values: [2.9, 4.9, 2.6] }
        ChartModelElement { values: [3.4, 3.0, 2.3] }
        ChartModelElement { values: [4.1, 3.3, 3.1] }
    }

}
