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


Flow {
    id: flow
    spacing: 5
    flow: Flow.TopToBottom
    property variant series // TODO: rename to chart

    Button {
        text: "visible"
        onClicked: series.visible = !series.visible;
    }
    Button {
        text: "theme +"
        onClicked: series.theme++;
    }
    Button {
        text: "theme -"
        onClicked: series.theme--;
    }
    Button {
        text: "animation opt +"
        onClicked: series.animationOptions++;
    }
    Button {
        text: "animation opt -"
        onClicked: series.animationOptions--;
    }
    Button {
        text: "title font bold"
        onClicked: series.titleFont.bold = !series.titleFont.bold;
    }
    Button {
        text: "title color"
        onClicked: series.titleColor = main.nextColor();
    }
    Button {
        text: "background color"
        onClicked: series.backgroundColor = main.nextColor();
    }
    Button {
        text: "drop shadow enabled"
        onClicked: series.dropShadowEnabled = !series.dropShadowEnabled;
    }
    Button {
        text: "zoom +"
        onClicked: series.zoom(2);
    }
    Button {
        text: "zoom -"
        onClicked: series.zoom(0.5);
    }
    Button {
        text: "scroll left"
        onClicked: series.scrollLeft(10);
    }
    Button {
        text: "scroll right"
        onClicked: series.scrollRight(10);
    }
    Button {
        text: "scroll up"
        onClicked: series.scrollUp(10);
    }
    Button {
        text: "scroll down"
        onClicked: series.scrollDown(10);
    }
    Button {
        text: "legend visible"
        onClicked: series.legend.visible = !series.legend.visible;
    }
    Button {
        text: "legend bckgrd visible"
        onClicked: series.legend.backgroundVisible = !series.legend.backgroundVisible;
    }
    Button {
        text: "legend color"
        onClicked: series.legend.color = main.nextColor();
    }
    Button {
        text: "legend border color"
        onClicked: series.legend.borderColor = main.nextColor();
    }
    Button {
        text: "legend top"
        onClicked: series.legend.alignment ^= Qt.AlignTop;
    }
    Button {
        text: "legend bottom"
        onClicked: series.legend.alignment ^= Qt.AlignBottom;
    }
    Button {
        text: "legend left"
        onClicked: series.legend.alignment ^= Qt.AlignLeft;
    }
    Button {
        text: "legend right"
        onClicked: series.legend.alignment ^= Qt.AlignRight;
    }
    Button {
        text: "axis X visible"
        onClicked: series.axisX.visible = !series.axisX.visible;
    }
    Button {
        text: "axis X grid visible"
        onClicked: series.axisX.gridVisible = !series.axisX.gridVisible;
    }
    Button {
        text: "axis X labels italic"
        onClicked: series.axisX.labelsFont.italic = !series.axisX.labelsFont.italic;
    }
    Button {
        text: "axis X labels visible"
        onClicked: series.axisX.labelsVisible = !series.axisX.labelsVisible;
    }
    Button {
        text: "axis X color"
        onClicked: series.axisX.color = main.nextColor();
    }
    Button {
        text: "axis X labels color"
        onClicked: series.axisX.labelsColor = main.nextColor();
    }
    Button {
        text: "axis X labels angle +"
        onClicked: series.axisX.labelsAngle += 5;
    }
    Button {
        text: "axis X labels angle -"
        onClicked: series.axisX.labelsAngle -= 5;
    }
    Button {
        text: "axis X shades visible"
        onClicked: series.axisX.shadesVisible = !series.axisX.shadesVisible;
    }
    Button {
        text: "axis X shades color"
        onClicked: series.axisX.shadesColor = main.nextColor();
    }
    Button {
        text: "axis X shades bcolor"
        onClicked: series.axisX.shadesBorderColor = main.nextColor();
    }
    Button {
        text: "axis X max +"
        onClicked: series.axisX.max += 0.1;
    }
    Button {
        text: "axis X max -"
        onClicked: series.axisX.max -= 0.1;
    }
    Button {
        text: "axis X min +"
        onClicked: series.axisX.min += 0.1;
    }
    Button {
        text: "axis X min -"
        onClicked: series.axisX.min -= 0.1;
    }
    Button {
        text: "axis X ticks count +"
        onClicked: series.axisX.ticksCount++;
    }
    Button {
        text: "axis X ticks count -"
        onClicked: series.axisX.ticksCount--;
    }
    Button {
        text: "axis X nice nmb"
        onClicked: series.axisX.niceNumbersEnabled = !series.axisX.niceNumbersEnabled;
    }
    Button {
        text: "axis Y visible"
        onClicked: series.axisY.visible = !series.axisY.visible;
    }
    Button {
        text: "axis Y grid visible"
        onClicked: series.axisY.gridVisible = !series.axisY.gridVisible;
    }
    Button {
        text: "axis Y labels visible"
        onClicked: series.axisY.labelsVisible = !series.axisY.labelsVisible;
    }
    Button {
        text: "axis Y color"
        onClicked: series.axisY.color = main.nextColor();
    }
    Button {
        text: "axis Y labels color"
        onClicked: series.axisY.labelsColor = main.nextColor();
    }
    Button {
        text: "axis Y labels angle +"
        onClicked: series.axisY.labelsAngle += 5;
    }
    Button {
        text: "axis Y labels angle -"
        onClicked: series.axisY.labelsAngle -= 5;
    }
    Button {
        text: "axis Y shades visible"
        onClicked: series.axisY.shadesVisible = !series.axisY.shadesVisible;
    }
    Button {
        text: "axis Y shades color"
        onClicked: series.axisY.shadesColor = main.nextColor();
    }
    Button {
        text: "axis Y shades bcolor"
        onClicked: series.axisY.shadesBorderColor = main.nextColor();
    }
    Button {
        text: "axis Y max +"
        onClicked: series.axisY.max += 0.1;
    }
    Button {
        text: "axis Y max -"
        onClicked: series.axisY.max -= 0.1;
    }
    Button {
        text: "axis Y min +"
        onClicked: series.axisY.min += 0.1;
    }
    Button {
        text: "axis Y min -"
        onClicked: series.axisY.min -= 0.1;
    }
    Button {
        text: "axis Y ticks count +"
        onClicked: series.axisY.ticksCount++;
    }
    Button {
        text: "axis Y ticks count -"
        onClicked: series.axisY.ticksCount--;
    }
    Button {
        text: "axis Y nice nmb"
        onClicked: series.axisY.niceNumbersEnabled = !series.axisY.niceNumbersEnabled;
    }
}
