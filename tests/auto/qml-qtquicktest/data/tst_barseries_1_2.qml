// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtTest 1.0
import QtCharts 1.2

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest BarSeries 1.2"
        when: windowShown

        function test_properties() {
            compare(barSeries.barWidth, 0.5);
            compare(barSeries.labelsVisible, false);
        }

        function test_axes() {
            verify(chartView.axisX() == barSeries.axisX);
            verify(chartView.axisY() == barSeries.axisY);

            compare(barSeries.axisX, stackedBarSeries.axisX);
            compare(barSeries.axisY, stackedBarSeries.axisY);

            compare(barSeries.axisX, percentBarSeries.axisX);
            compare(barSeries.axisY, percentBarSeries.axisY);
        }

        function test_append() {
            var setCount = 5;
            var valueCount = 50;
            addedSpy.clear();
            append(setCount, valueCount);

            compare(barSeries.count, setCount);
            for (var k = 0; k < setCount; k++) {
                compare(barSeries.at(k).count, valueCount);
                compare(barSeries.at(k).label, "barset" + k);
            }
            compare(addedSpy.count, setCount);

            barSeries.clear();
            compare(barSeries.count, 0);
        }

        function test_insert() {
            var setCount = 5;
            var valueCount = 50;
            addedSpy.clear();
            append(setCount, valueCount);

            for (var i = 0; i < setCount; i++) {
                var values = [];
                for (var j = 0; j < valueCount; j++)
                    values[j] = Math.random() * 10;
                var set = barSeries.insert(i, "barset" + i, values);
                compare(set.label, "barset" + i);
            }

            compare(barSeries.count, setCount * 2);
            for (var k = 0; k < setCount * 2; k++)
                compare(barSeries.at(k).count, valueCount);
            compare(addedSpy.count, 2 * setCount);

            barSeries.clear();
            compare(barSeries.count, 0);
        }

        function test_remove() {
            var setCount = 5;
            var valueCount = 50;
            removedSpy.clear();
            append(setCount, valueCount);

            for (var k = 0; k < setCount; k++)
                barSeries.remove(barSeries.at(0));

            compare(barSeries.count, 0);
            compare(removedSpy.count, setCount);
        }

        // Not a test function, used by one or more test functions
        function append(setCount, valueCount) {
            for (var i = 0; i < setCount; i++) {
                var values = [];
                for (var j = 0; j < valueCount; j++)
                    values[j] = Math.random() * 10;
                barSeries.append("barset" + i, values);
            }
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        BarSeries {
            id: barSeries
            name: "bar"
            axisX: BarCategoryAxis {}
            axisY: ValueAxis { min: 0; max: 10 }

            SignalSpy {
                id: addedSpy
                target: barSeries
                signalName: "barsetsAdded"
            }
            SignalSpy {
                id: removedSpy
                target: barSeries
                signalName: "barsetsRemoved"
            }
        }

        StackedBarSeries {
            id: stackedBarSeries
            name: "stackedBar"
        }

        PercentBarSeries {
            id: percentBarSeries
            name: "percentBar"
        }
    }
}
