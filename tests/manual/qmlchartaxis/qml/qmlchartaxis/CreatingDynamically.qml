/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    id: chartView
    title: "creating dyn. new series"
    property int index: 0

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            switch (index) {
            case 0:
                var count = chartView.count;
                var line = chartView.createSeries(ChartView.SeriesTypeLine, "line");
                line.append(0, 0);
                line.append(1, 1);
                line.append(2, 2);
                line.append(3, 3);
                line.append(4, 4);
                break;
            case 1:
                chartView.axisX().min = 0;
                chartView.axisX().max = 4.5;
                chartView.axisY().min = 0;
                chartView.axisY().max = 4.5;
                break;
            case 2:
                var scatter = chartView.createSeries(ChartView.SeriesTypeScatter, "scatter");
                scatter.append(0, 0);
                scatter.append(0.5, 1);
                scatter.append(1, 2);
                scatter.append(1.5, 3);
                scatter.append(2, 4);
                scatter.append(1, 1);
                scatter.append(2, 2);
                scatter.append(3, 3);
                scatter.append(4, 4);
                break;
            default:
                chartView.removeAllSeries();
            }
            index = (index + 1) % 4;
        }
    }
}
