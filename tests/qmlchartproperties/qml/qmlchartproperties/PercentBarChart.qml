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
    title: "Percent bar series"
    anchors.fill: parent
    theme: ChartView.ChartThemeLight
    legend.alignment: Qt.AlignBottom
    axisXLabels: ["0", "2007", "1", "2008", "2", "2009", "3", "2010", "4", "2011", "5", "2012"]

    property variant series: daSeries

    PercentBarSeries {
        id: daSeries
        name: "bar"
        BarSet { label: "Bob"; values: [2, 2, 3, 4, 5, 6] }
        BarSet { label: "Susan"; values: [5, 1, 2, 4, 1, 7] }
        BarSet { label: "James"; values: [3, 5, 8, 13, 5, 8] }
    }
}
