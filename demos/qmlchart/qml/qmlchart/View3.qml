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

    ChartView {
        title: "NHL All-Star Team Players"
        anchors.fill: parent
        theme: ChartView.ChartThemeHighContrast
        axisXLabels: ["0", "2000", "1", "2001", "2", "2002", "3", "2003", "4", "2004", "5", "2005",
            "6", "2006", "7", "2007", "8", "2008", "9", "2009", "10", "2010", "11", "2011"]

        AreaSeries {
            name: "Russian"
            upperSeries: LineSeries {
                XyPoint { x: 0; y: 1 }
                XyPoint { x: 1; y: 1 }
                XyPoint { x: 2; y: 1 }
                XyPoint { x: 3; y: 1 }
                XyPoint { x: 4; y: 1 }
                XyPoint { x: 5; y: 0 }
                XyPoint { x: 6; y: 1 }
                XyPoint { x: 7; y: 1 }
                XyPoint { x: 8; y: 4 }
                XyPoint { x: 9; y: 3 }
                XyPoint { x: 10; y: 2 }
                XyPoint { x: 11; y: 1 }
            }
            lowerSeries: LineSeries {
                XyPoint { x: 0; y: 0 }
                XyPoint { x: 1; y: 0 }
                XyPoint { x: 2; y: 0 }
                XyPoint { x: 3; y: 0 }
                XyPoint { x: 4; y: 0 }
                XyPoint { x: 5; y: 0 }
                XyPoint { x: 6; y: 0 }
                XyPoint { x: 7; y: 0 }
                XyPoint { x: 8; y: 0 }
                XyPoint { x: 9; y: 0 }
                XyPoint { x: 10; y: 0 }
                XyPoint { x: 11; y: 0 }
            }
        }

        AreaSeries {
            name: "Swedish"
            upperSeries: LineSeries {
                XyPoint { x: 0; y: 1 }
                XyPoint { x: 1; y: 1 }
                XyPoint { x: 2; y: 3 }
                XyPoint { x: 3; y: 3 }
                XyPoint { x: 4; y: 2 }
                XyPoint { x: 5; y: 0 }
                XyPoint { x: 6; y: 2 }
                XyPoint { x: 7; y: 1 }
                XyPoint { x: 8; y: 2 }
                XyPoint { x: 9; y: 1 }
                XyPoint { x: 10; y: 3 }
                XyPoint { x: 11; y: 3 }
            }
            lowerSeries: LineSeries {
                XyPoint { x: 0; y: 0 }
                XyPoint { x: 1; y: 0 }
                XyPoint { x: 2; y: 0 }
                XyPoint { x: 3; y: 0 }
                XyPoint { x: 4; y: 0 }
                XyPoint { x: 5; y: 0 }
                XyPoint { x: 6; y: 0 }
                XyPoint { x: 7; y: 0 }
                XyPoint { x: 8; y: 0 }
                XyPoint { x: 9; y: 0 }
                XyPoint { x: 10; y: 0 }
                XyPoint { x: 11; y: 0 }
            }
        }

        AreaSeries {
            name: "Finnish"
            upperSeries: LineSeries {
                XyPoint { x: 0; y: 0 }
                XyPoint { x: 1; y: 0 }
                XyPoint { x: 2; y: 0 }
                XyPoint { x: 3; y: 0 }
                XyPoint { x: 4; y: 0 }
                XyPoint { x: 5; y: 0 }
                XyPoint { x: 6; y: 1 }
                XyPoint { x: 7; y: 0 }
                XyPoint { x: 8; y: 0 }
                XyPoint { x: 9; y: 0 }
                XyPoint { x: 10; y: 0 }
                XyPoint { x: 11; y: 1 }
            }
            lowerSeries: LineSeries {
                XyPoint { x: 0; y: 0 }
                XyPoint { x: 1; y: 0 }
                XyPoint { x: 2; y: 0 }
                XyPoint { x: 3; y: 0 }
                XyPoint { x: 4; y: 0 }
                XyPoint { x: 5; y: 0 }
                XyPoint { x: 6; y: 0 }
                XyPoint { x: 7; y: 0 }
                XyPoint { x: 8; y: 0 }
                XyPoint { x: 9; y: 0 }
                XyPoint { x: 10; y: 0 }
                XyPoint { x: 11; y: 0 }
            }
        }
    }
}
