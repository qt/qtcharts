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
import QtTest 1.0
import QtCharts 1.2

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest ChartView Signals 1.2"
        when: windowShown

        // Verify onSeriesAdded and onSeriesRemoved signals
        function test_chartView() {
            var series = chartView.createSeries(ChartView.SeriesTypeLine, "line");
            seriesAddedSpy.wait();
            compare(seriesAddedSpy.count, 1, "ChartView.onSeriesAdded");

            // Modifying layout triggers more than one plotAreaChanged signal
            chartView.titleFont.pixelSize = 50;
            verify(plotAreaChangedSpy.count > 0, "ChartView.onPlotAreaChanged");

            chartView.removeSeries(series);
            seriesRemovedSpy.wait();
            compare(seriesRemovedSpy.count, 1, "ChartView.onSeriesAdded");
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent
        title: "Chart"

        SignalSpy {
            id: plotAreaChangedSpy
            target: chartView
            signalName: "plotAreaChanged"
        }

        SignalSpy {
            id: seriesAddedSpy
            target: chartView
            signalName: "seriesAdded"
        }

        SignalSpy {
            id: seriesRemovedSpy
            target: chartView
            signalName: "seriesRemoved"
        }
    }
}
