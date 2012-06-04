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
    title: "Bar series"
    anchors.fill: parent
    theme: ChartView.ChartThemeLight
    legend.alignment: Qt.AlignBottom
    axisXLabels: ["0", "2007", "1", "2008", "2", "2009", "3", "2010", "4", "2011", "5", "2012"]

    property variant series: daSeries

    BarSeries {
        id: daSeries
        BarSet { name: "Bob"; values: [4, 7, 3, 10, 5, 6] }
        BarSet { name: "Susan"; values: [5, 1, 2, 4, 1, 8] }
        BarSet { name: "James"; values: [3, 5, 8, 5, 4, 7] }
    }
}
