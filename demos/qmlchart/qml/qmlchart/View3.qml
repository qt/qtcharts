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
        title: "NHL All-Star Team Players"
        anchors.fill: parent
        theme: ChartView.ChartThemeHighContrast
        axisXLabels: ["0", "2000", "1", "2001", "2", "2002", "3", "2003", "4", "2004", "5", "2005",
            "6", "2006", "7", "2007", "8", "2008", "9", "2009", "10", "2010", "11", "2011"]

        AreaSeries {
            name: "Russian"
            upperModel: chartModel
            upperModelMapper.mapX: 0
            upperModelMapper.mapY: 2
            lowerModel: chartModel
            lowerModelMapper.mapX: 0
            lowerModelMapper.mapY: 1
        }
        AreaSeries {
            name: "Swedish"
            upperModel: chartModel
            upperModelMapper.mapX: 0
            upperModelMapper.mapY: 3
            lowerModel: chartModel
            lowerModelMapper.mapX: 0
            lowerModelMapper.mapY: 1
        }
        AreaSeries {
            name: "Finnish"
            upperModel: chartModel
            upperModelMapper.mapX: 0
            upperModelMapper.mapY: 4
            lowerModel: chartModel
            lowerModelMapper.mapX: 0
            lowerModelMapper.mapY: 1
        }
    }

    ChartModel {
        id: chartModel
        ChartModelRow { values: [0,  0, 1, 1, 0] }
        ChartModelRow { values: [1,  0, 1, 1, 0] }
        ChartModelRow { values: [2,  0, 1, 3, 0] }
        ChartModelRow { values: [3,  0, 1, 3, 0] }
        ChartModelRow { values: [4,  0, 1, 2, 0] }
        ChartModelRow { values: [5,  0, 0, 0, 0] }
        ChartModelRow { values: [6,  0, 1, 2, 1] }
        ChartModelRow { values: [7,  0, 1, 1, 0] }
        ChartModelRow { values: [8,  0, 4, 2, 0] }
        ChartModelRow { values: [9,  0, 3, 1, 0] }
        ChartModelRow { values: [10, 0, 2, 3, 0] }
        ChartModelRow { values: [11, 0, 1, 3, 1] }
    }
}
