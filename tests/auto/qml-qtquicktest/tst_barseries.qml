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

import QtQuick 1.0
import QtQuickTest 1.0
import QtCommercial.Chart 1.2

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest BarSeries"
        when: windowShown

        function test_properties() {
            compare(barSeries.barWidth, 0.5);
            compare(barSeries.labelsVisible, false);
        }

        function test_axes() {
            compare(chartView.axes.length, 2);
            verify(chartView.axes[0] == barSeries.axisX || chartView.axes[1] == barSeries.axisX);
            verify(chartView.axes[0] == barSeries.axisY || chartView.axes[1] == barSeries.axisY);

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
