/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

//![1]
import QtQuick 1.0
import QtCommercial.Chart 1.1

ChartView {
    title: "Box Plot series"
    width: 400
    height: 300
    theme: ChartView.ChartThemeBrownSand
    legend.alignment: Qt.AlignBottom

//![1]
//![2]
    BoxPlotSeries {
        id: plotSeries
        name: "Income"
        axisX: BarCategoryAxis { categories: ["Jan", "Feb", "Mar", "Apr", "May"] }
        BarSet { label: "Jan"; values: [3, 4, 4.4, 6, 7] }
        BarSet { label: "Feb"; values: [5, 6, 7.5, 8, 12] }
        BarSet { label: "Mar"; values: [2, 5, 5.7, 8, 9] }
        BarSet { label: "Apr"; values: [5, 6, 6.8, 7, 8] }
        BarSet { label: "May"; values: [4, 5, 5.2, 6, 7] }
    }
//![2]


//![3]
}
//![3]
