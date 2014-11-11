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

    BoxPlotSeries {
        name: "BoxPlotSeries"
        BoxSet { label: "Set1"; values: [3, 4, 5.1, 6.2, 8.5] }
        BoxSet { label: "Set2"; values: [5, 6, 7.5, 8.6, 11.8] }
        BoxSet { label: "Set3"; values: [3.2, 5, 5.7, 8, 9.2] }
    }
}
