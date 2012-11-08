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
import QtQuickTest 1.0
import QtCommercial.Chart 1.1

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest ChartView Properties 1.1"
        when: windowShown

        function test_chartViewProperties() {
            compare(chartView.animationOptions, ChartView.NoAnimation, "ChartView.animationOptions");
            verify(chartView.backgroundColor != undefined);
            verify(chartView.bottomMargin > 0, "ChartView.bottomMargin");
            verify(chartView.topMargin > 0, "ChartView.topMargin");
            verify(chartView.leftMargin > 0, "ChartView.leftMargin");
            verify(chartView.rightMargin > 0, "ChartView.rightMargin");
            compare(chartView.count, 0, "ChartView.count");
            compare(chartView.dropShadowEnabled, false, "ChartView.dropShadowEnabled");
            verify(chartView.plotArea.height > 0, "ChartView.plotArea.height");
            verify(chartView.plotArea.width > 0, "ChartView.plotArea.width");
            verify(chartView.plotArea.x > 0, "ChartView.plotArea.x");
            verify(chartView.plotArea.y > 0, "ChartView.plotArea.y");
            compare(chartView.theme, ChartView.ChartThemeLight, "ChartView.theme");
            compare(chartView.title, "", "ChartView.title");
            compare(chartView.title, "", "ChartView.title");
            verify(chartView.titleColor != undefined, "ChartView.titleColor");
            compare(chartView.titleFont.bold, false, "ChartView.titleFont.bold");
            // Legend
            compare(chartView.legend.visible, true, "ChartView.legend.visible");
            compare(chartView.legend.alignment, Qt.AlignTop, "ChartView.legend.alignment");
            compare(chartView.legend.backgroundVisible, false, "ChartView.legend.backgroundVisible");
            verify(chartView.legend.borderColor != undefined, "ChartView.legend.borderColor");
            verify(chartView.legend.color != undefined, "ChartView.legend.color");
            // Legend font
            compare(chartView.legend.font.bold, false, "ChartView.legend.font.bold");
            compare(chartView.legend.font.capitalization, Font.MixedCase, "ChartView.legend.font.capitalization");
            compare(chartView.legend.font.family, "arial", "ChartView.legend.font.family");
            compare(chartView.legend.font.italic, false, "ChartView.legend.font.italic");
            compare(chartView.legend.font.letterSpacing, 0.0, "ChartView.legend.font.letterSpacing");
            verify(chartView.legend.font.pixelSize > 0
                   && chartView.legend.font.pixelSize < 50, "ChartView.legend.font.pixelSize");
            verify(chartView.legend.font.pointSize > 0
                   && chartView.legend.font.pointSize < 50, "ChartView.legend.font.pointSize");
            compare(chartView.legend.font.strikeout, false, "ChartView.legend.font.strikeout");
            compare(chartView.legend.font.underline, false, "ChartView.legend.font.underline");
            compare(chartView.legend.font.weight, Font.Normal, "ChartView.legend.font.weight");
            compare(chartView.legend.font.wordSpacing, 0.0, "ChartView.legend.font.wordSpacing");
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent
    }
}
