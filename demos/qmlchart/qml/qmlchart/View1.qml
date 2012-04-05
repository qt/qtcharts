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
import QtCommercial.Chart 1.0

Rectangle {
    anchors.fill: parent

    Chart {
        title: "Car brand shares in Finland"
        anchors.fill: parent
        theme: Chart.ChartThemeLight

        PieSeries {
            horizontalPosition: 0.2
            verticalPosition: 0.3
            size: 0.4
            slices: [
                PieSlice { label: "Volkswagen"; value: 13.5 },
                PieSlice { label: "Toyota"; value: 10.9 },
                PieSlice { label: "Ford"; value: 8.6 },
                PieSlice { label: "Skoda"; value: 8.2 },
                PieSlice { label: "Volvo"; value: 6.8 },
                PieSlice { label: "Others"; value: 52.0 }
            ]
        }

        BarSeries {
            barCategories: [ "2008", "2009", "2010", "2011", "2012" ]
            // data implementation missing
        }
    }
}
