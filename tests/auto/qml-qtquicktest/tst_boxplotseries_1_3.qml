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
        name: "tst_qml-qtquicktest BoxPlotSeries 1.3"
        when: windowShown

        function test_properties() {
            compare(boxPlotSeries.boxWidth, 0.5);
        }

        function test_setproperties() {
            var set = boxPlotSeries.append("boxplot", [1, 2, 5, 6, 8]);
            compare(set.label, "boxplot");
            compare(set.count, 5);
        }

        function test_append() {
            addedSpy.clear();
            countChangedSpy.clear();
            var count = 50;
            for (var i = 0; i < count; i++)
                boxPlotSeries.append("boxplot" + i, Math.random());
            compare(addedSpy.count, count);
            compare(countChangedSpy.count, count);
            console.log("Check the series count once QTRD-2504 is implemented");
            boxPlotSeries.clear();
        }

        function test_remove() {
            removedSpy.clear();
            countChangedSpy.clear();
            var count = 50;
            for (var i = 0; i < count; i++)
                boxPlotSeries.append("boxplot" + i, Math.random());
            for (var j = 0; j < count; j++)
                boxPlotSeries.remove(boxPlotSeries.at(0));
            compare(removedSpy.count, count);
            compare(countChangedSpy.count, 2 * count);
            console.log("Check the series count once QTRD-2504 is implemented");
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        BoxPlotSeries {
            id: boxPlotSeries
            name: "boxplot"
            BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5] }

            SignalSpy {
                id: addedSpy
                target: boxPlotSeries
                signalName: "boxsetsAdded"
            }
            SignalSpy {
                id: removedSpy
                target: boxPlotSeries
                signalName: "boxsetsRemoved"
            }
            SignalSpy {
                id: countChangedSpy
                target: boxPlotSeries
                signalName: "countChanged"
            }
        }
    }
}
