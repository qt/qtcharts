// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
        text: series != undefined ? "width + (" + series.width + ")" : ""
        onClicked: series.width += 0.5;
    }
    Button {
        text: series != undefined ? "width - (" + series.width + ")" : ""
        onClicked: series.width -= 0.5;
    }
    Button {
        text: series != undefined ? "style + (" + series.style + ")" : ""
        onClicked: series.style++;
    }
    Button {
        text: series != undefined ? "style - (" + series.style + ")" : ""
        onClicked: series.style--;
    }
    Button {
        text: series != undefined ? "cap style + (" + series.capStyle + ")" : ""
        onClicked: series.capStyle++;
    }
    Button {
        text: series != undefined ? "cap style - (" +series.capStyle + ")" : ""
        onClicked: series.capStyle--;
    }
    Button {
        text: "points visible"
        onClicked: series.pointsVisible = !series.pointsVisible;
    }
    Button {
        text: "point labels visible"
        onClicked: series.pointLabelsVisible = !series.pointLabelsVisible;
    }
    Button {
        text: "point labels format"
        onClicked: {
            if (series.pointLabelsFormat === "@xPoint, @yPoint")
                series.pointLabelsFormat = "(@xPoint)"
            else
                series.pointLabelsFormat = "@xPoint, @yPoint"
        }
    }
    Button {
        text: "point labels font"
        onClicked: {
            if (series.pointLabelsFont.family === "Times")
                series.pointLabelsFont.family = "Courier";
            else
                series.pointLabelsFont.family = "Times";
        }
    }
    Button {
        text: "point labels color"
        onClicked: series.pointLabelsColor = main.nextColor();
    }
    Button {
        text: "point labels clipping"
        onClicked: series.pointLabelsClipping = !series.pointLabelsClipping;
    }
    Button {
        text: "append point"
        onClicked: series.append(series.count - 1, series.count - 1);
    }
    Button {
        text: "replace point"
        onClicked: {
            var xyPoint = series.at(series.count - 1);
            series.replace(series.count - 1, xyPoint.x, xyPoint.y + 0.1);
        }
    }
    Button {
        text: "remove point"
        onClicked: series.remove(series.count - 1);
    }
    Button {
        text: "remove points"
        onClicked: {
            var count = 3;
            if (series.count < 3)
                count = series.count
            var index = series.count - count;
            series.removePoints(index, count);
        }
    }
    Button {
        text: "insert point"
        onClicked: series.insert(series.count - 2, series.count - 2, series.count - 2);
    }
    Button {
        text: "clear"
        onClicked: series.clear();
    }
    Button {
        text: "toggle useOpenGL"
        onClicked: series.useOpenGL = !series.useOpenGL
    }
}
