/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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
import QtTest 1.0
import QtCommercial.Chart 1.3

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest ChartView Signals 1.3"
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
