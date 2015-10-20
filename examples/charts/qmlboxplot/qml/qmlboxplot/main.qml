/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
