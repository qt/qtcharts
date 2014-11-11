/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    width: 300
    height: 300

    AreaSeries {
        name: "AreaSeries"
        upperSeries: LineSeries {
            XYPoint { x: 0; y: 1.5 }
            XYPoint { x: 1; y: 3 }
            XYPoint { x: 3; y: 4.3 }
            XYPoint { x: 6; y: 1.1 }
        }
    }
}
