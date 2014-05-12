/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

//![1]
import QtQuick 1.0
import QtCommercial.Chart 1.1

ChartView {
    width: 400
    height: 300
    theme: ChartView.ChartThemeBrownSand

//![1]
//![2]
    PieSeries {
        id: pieSeries
        PieSlice { label: "eaten"; value: 94.9 }
        PieSlice { label: "not yet eaten"; value: 5.1 }
    }
//![2]

    Component.onCompleted: {
        if (false) {
            //![4]
            pieSeries.append("don't care", 1.1);
            //![4]

            //![5]
            pieSeries.at(0).exploded = true;
            //![5]
        }
    }

//![3]
}
//![3]
