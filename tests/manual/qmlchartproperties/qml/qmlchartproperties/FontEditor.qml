// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0

Flow {
    flow: Flow.TopToBottom
    spacing: 5
    property string fontDescription: ""

    Button {
        text: fontDescription + " bold"
        onClicked: editedFont().bold = !editedFont().bold;
    }
    Button {
        text: fontDescription + " capitalization"
        onClicked: editedFont().capitalization++;
    }
    Button {
        text: fontDescription + " font family"
        onClicked: editedFont().family = "courier";
    }
    Button {
        text: fontDescription + " font italic"
        onClicked: editedFont().italic = !editedFont().italic;
    }
    Button {
        text: fontDescription + " letterSpacing +"
        onClicked: editedFont().letterSpacing++;
    }
    Button {
        text: fontDescription + " letterSpacing -"
        onClicked: editedFont().letterSpacing--;
    }
    Button {
        text: fontDescription + " pixelSize +"
        onClicked: editedFont().pixelSize++;
    }
    Button {
        text: fontDescription + " pixelSize -"
        onClicked: editedFont().pixelSize--;
    }
    Button {
        text: fontDescription + " pointSize +"
        onClicked: editedFont().pointSize++;
    }
    Button {
        text: fontDescription + " pointSize -"
        onClicked: editedFont().pointSize--;
    }
    Button {
        text: fontDescription + " strikeout"
        onClicked: editedFont().strikeout = !editedFont().strikeout;
    }
    Button {
        text: fontDescription + " underline"
        onClicked: editedFont().underline = !editedFont().underline;
    }
    Button {
        text: fontDescription + " weight +"
        onClicked: editedFont().weight++;
    }
    Button {
        text: fontDescription + " weight -"
        onClicked: editedFont().weight--;
    }
    Button {
        text: fontDescription + " wordSpacing +"
        onClicked: editedFont().wordSpacing++;
    }
    Button {
        text: fontDescription + " wordSpacing -"
        onClicked: editedFont().wordSpacing--;
    }
}
