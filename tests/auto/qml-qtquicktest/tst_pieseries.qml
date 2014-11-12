/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import QtTest 1.0
import QtCharts 2.0

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest PieSeries"
        when: windowShown

        function test_properties() {
            compare(pieSeries.endAngle, 360);
            compare(pieSeries.holeSize, 0);
            compare(pieSeries.horizontalPosition, 0.5);
            compare(pieSeries.size, 0.7);
            compare(pieSeries.startAngle, 0);
            compare(pieSeries.sum, 0);
            compare(pieSeries.verticalPosition, 0.5);
        }

        function test_sliceproperties() {
            var slice = pieSeries.append("slice", 10);
            compare(slice.angleSpan, 360.0);
            verify(slice.borderColor != undefined);
            compare(slice.borderWidth, 1);
            verify(slice.color != undefined);
            compare(slice.explodeDistanceFactor, 0.15);
            compare(slice.exploded, false);
            compare(slice.label, "slice");
            compare(slice.labelArmLengthFactor, 0.15);
            verify(slice.labelColor != undefined);
            compare(slice.labelFont.bold, false);
            compare(slice.labelPosition, PieSlice.LabelOutside);
            compare(slice.labelVisible, false);
            compare(slice.percentage, 1.0);
            compare(slice.startAngle, 0.0);
            compare(slice.value, 10.0);
            compare(slice.brushFilename, "");
        }

        function test_append() {
            addedSpy.clear();
            countChangedSpy.clear();
            sumChangedSpy.clear();
            var count = 50;
            for (var i = 0; i < count; i++)
                pieSeries.append("slice" + i, Math.random());
            compare(addedSpy.count, count);
            compare(countChangedSpy.count, count);
            compare(sumChangedSpy.count, count);
            pieSeries.clear();
        }

        function test_remove() {
            removedSpy.clear();
            countChangedSpy.clear();
            sumChangedSpy.clear();
            var count = 50;
            for (var i = 0; i < count; i++)
                pieSeries.append("slice" + i, Math.random());
            for (var j = 0; j < count; j++)
                pieSeries.remove(pieSeries.at(0));
            compare(removedSpy.count, count);
            compare(countChangedSpy.count, 2 * count);
            compare(sumChangedSpy.count, 2 * count);
            compare(pieSeries.count, 0);
        }

        function test_find_and_at() {
            var count = 50;
            for (var i = 0; i < count; i++)
                pieSeries.append("slice" + i, Math.random());
            for (var j = 0; j < count; j++) {
                compare(pieSeries.find("slice" + j).label, "slice" + j);
                compare(pieSeries.find("slice" + j).brushFilename, "");
            }
            compare(pieSeries.at(3).brushFilename,"");
            pieSeries.clear();
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        PieSeries {
            id: pieSeries
            name: "pie"

            SignalSpy {
                id: addedSpy
                target: pieSeries
                signalName: "added"
            }
            SignalSpy {
                id: removedSpy
                target: pieSeries
                signalName: "removed"
            }
            SignalSpy {
                id: sumChangedSpy
                target: pieSeries
                signalName: "sumChanged"
            }
            SignalSpy {
                id: countChangedSpy
                target: pieSeries
                signalName: "countChanged"
            }
        }
    }
}
