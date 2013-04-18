/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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
        text: "markerSize +"
        onClicked: series.markerSize += 1.0;
    }
    Button {
        text: "markerSize -"
        onClicked: series.markerSize -= 1.0;
    }
    Button {
        text: "markerShape"
        onClicked: series.markerShape = ((series.markerShape + 1) % 2);
    }
    Button {
        text: "append point"
        onClicked: series.append(series.count - 1, series.count - 1);
    }
    Button {
        text: "replace point"
        onClicked: {
            var xyPoint = series.at(series.count - 1);
            series.replace(xyPoint.x, xyPoint.y, xyPoint.x, xyPoint.y + 0.1);
        }
    }
    Button {
        text: "remove point"
        onClicked: series.remove(series.at(series.count - 1).x, series.at(series.count - 1).y);
    }
    Button {
        text: "insert point"
        onClicked: series.insert(series.count - 2, series.count - 2, series.count - 2);
    }
    Button {
        text: "clear"
        onClicked: series.clear();
    }
}
