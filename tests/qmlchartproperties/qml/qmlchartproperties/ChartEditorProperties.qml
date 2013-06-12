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

Flow {
    anchors.fill: parent
    property variant chart
    flow: Flow.TopToBottom
    spacing: 5
    Button {
        text: "visible"
        onClicked: chart.visible = !chart.visible;
    }
    Button {
        text: "theme +"
        onClicked: chart.theme++;
    }
    Button {
        text: "theme -"
        onClicked: chart.theme--;
    }
    Button {
        text: "animation opt +"
        onClicked: chart.animationOptions++;
    }
    Button {
        text: "animation opt -"
        onClicked: chart.animationOptions--;
    }
    Button {
        text: "background color"
        onClicked: chart.backgroundColor = main.nextColor();
    }
    Button {
        text: "plot area color"
        onClicked: chart.plotAreaColor = main.nextColor();
    }
    Button {
        text: "drop shadow enabled"
        onClicked: chart.dropShadowEnabled = !chart.dropShadowEnabled;
    }
    Button {
        text: "roundness"
        onClicked: chart.backgroundRoundness++;
    }
    Button {
        text: "zoom +"
        onClicked: chart.zoom(2);
    }
    Button {
        text: "zoom -"
        onClicked: chart.zoom(0.5);
    }
    Button {
        text: "scroll left"
        onClicked: chart.scrollLeft(10);
    }
    Button {
        text: "scroll right"
        onClicked: chart.scrollRight(10);
    }
    Button {
        text: "scroll up"
        onClicked: chart.scrollUp(10);
    }
    Button {
        text: "scroll down"
        onClicked: chart.scrollDown(10);
    }
    Button {
        text: "title color"
        onClicked: chart.titleColor = main.nextColor();
    }
    Button {
        text: "top margin +"
        onClicked: chart.margins.top += 5;
    }
    Button {
        text: "top margin -"
        onClicked: chart.margins.top -= 5;
    }
    Button {
        text: "bottom margin +"
        onClicked: chart.margins.bottom += 5;
    }
    Button {
        text: "bottom margin -"
        onClicked: chart.margins.bottom -= 5;
    }
    Button {
        text: "left margin +"
        onClicked: chart.margins.left += 5;
    }
    Button {
        text: "left margin -"
        onClicked: chart.margins.left -= 5;
    }
    Button {
        text: "right margin +"
        onClicked: chart.margins.right += 5;
    }
    Button {
        text: "right margin -"
        onClicked: chart.margins.right -= 5;
    }
}
