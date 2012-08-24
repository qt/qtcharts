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

    //![1]
    ChartView {
        id: chart
        title: "Production costs"
        anchors.fill: parent
        legend.visible: false

        PieSeries {
            id: pieOuter
            size: 0.96
            PieSlice { id: slice; label: "Alpha"; value: 19511; color: "#2D6960"; borderColor: "#163430" }
            PieSlice { label: "Epsilon"; value: 11105; color: "#EFE672"; borderColor: "#3B391C" }
            PieSlice { label: "Psi"; value: 9352; color: "#4C1B33"; borderColor: "#13060C" }
        }

        PieSeries {
            size: 0.7
            id: pieInner

            PieSlice { label: "Materials"; value: 10334; color: "#618E87"; borderColor: "#163430" }
            PieSlice { label: "Employee"; value: 3066; color: "#2D6960"; borderColor: "#163430"; borderWidth: 2 }
            PieSlice { label: "Logistics"; value: 6111; color: "#214E48"; borderColor: "#163430"; borderWidth: 2 }

            PieSlice { label: "Materials"; value: 7371; color: "#F7F28B"; borderColor: "#3B391C"; borderWidth: 2 }
            PieSlice { label: "Employee"; value: 2443; color: "#EFE672"; borderColor: "#3B391C"; borderWidth: 2 }
            PieSlice { label: "Logistics"; value: 1291; color: "#777339"; borderColor: "#3B391C"; borderWidth: 2 }

            PieSlice { label: "Materials"; value: 4022; color: "#785466"; borderColor: "#13060C"; borderWidth: 2 }
            PieSlice { label: "Employee"; value: 3998; color: "#4C1B33"; borderColor: "#13060C"; borderWidth: 2 }
            PieSlice { label: "Logistics"; value: 1332; color: "#260D19"; borderColor: "#13060C"; borderWidth: 2 }
        }
    }
    //![1]

    Component.onCompleted: {
        // Set the common slice properties dynamically for convenience
        for (var i = 0; i < pieOuter.count; i++) {
            pieOuter.at(i).labelPosition = PieSlice.LabelOutside;
            pieOuter.at(i).labelVisible = true;
            pieOuter.at(i).borderWidth = 2;
        }
        for (var i = 0; i < pieInner.count; i++) {
            pieInner.at(i).labelPosition = PieSlice.LabelInsideNormal;
            pieInner.at(i).labelVisible = true;
            pieInner.at(i).borderWidth = 2;
        }
    }
}
