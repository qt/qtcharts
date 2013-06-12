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

Flow {
    id: flow
    spacing: 5
    flow: Flow.TopToBottom
    property variant series

    Button {
        text: "visible"
        onClicked: series.visible = !series.visible;
    }
    Button {
        text: "opacity +"
        onClicked: series.opacity += 0.1;
    }
    Button {
        text: "opacity -"
        onClicked: series.opacity -= 0.1;
    }
    Button {
        text: "color"
        onClicked: series.color = main.nextColor();
    }
    Button {
        text: "borderColor"
        onClicked: series.borderColor = main.nextColor();
    }
    Button {
        text: series != undefined ? "borderWidth + (" + series.borderWidth + ")" : ""
        onClicked: series.borderWidth += 0.5;
    }
    Button {
        text: series != undefined ? "borderWidth - (" + series.borderWidth + ")" : ""
        onClicked: series.borderWidth -= 0.5;
    }
    Button {
        id: upperButton
        text: "upper series"
        unpressedColor: "#79bd8f"
        onClicked: {
            lineEditor.visible = true;
            color = "#00a388";
            lowerButton.color = "#79bd8f";
            lineEditor.series = series.upperSeries;
        }
    }
    Button {
        id: lowerButton
        text: "lower series"
        unpressedColor: "#79bd8f"
        onClicked: {
            lineEditor.visible = true;
            color = "#00a388";
            upperButton.color = "#79bd8f";
            lineEditor.series = series.lowerSeries;
        }
    }
    LineEditor {
        id: lineEditor
        visible: false
    }

    onSeriesChanged: lineEditor.series = series.upperSeries;
}
