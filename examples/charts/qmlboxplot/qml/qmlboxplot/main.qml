/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    title: "Box Plot series"
    width: 400
    height: 300
    theme: ChartView.ChartThemeBrownSand
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    BoxPlotSeries {
        id: plotSeries
        name: "Income"
        BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5] }
        BoxSet { label: "Feb"; values: [5, 6, 7.5, 8.6, 11.8] }
        BoxSet { label: "Mar"; values: [3.2, 5, 5.7, 8, 9.2] }
        BoxSet { label: "Apr"; values: [3.8, 5, 6.4, 7, 8] }
        BoxSet { label: "May"; values: [4, 5, 5.2, 6, 7] }
    }
}
