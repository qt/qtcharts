// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtCharts

ChartView {
    title: "Candlestick Chart"
    width: 800
    height: 600
    theme: ChartView.ChartThemeLight
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    CandlestickSeries {
        name: "Acme Ltd."
        increasingColor: "green"
        decreasingColor: "red"

        CandlestickSet { timestamp: 1435708800000; open: 6.90; high: 6.94; low: 5.99; close: 6.60 }
        CandlestickSet { timestamp: 1435795200000; open: 6.69; high: 6.69; low: 6.69; close: 6.69 }
        CandlestickSet { timestamp: 1436140800000; open: 4.85; high: 6.23; low: 4.85; close: 6.00 }
        CandlestickSet { timestamp: 1436227200000; open: 5.89; high: 6.15; low: 3.77; close: 5.69 }
        CandlestickSet { timestamp: 1436313600000; open: 4.64; high: 4.64; low: 2.54; close: 2.54 }
    }
}
