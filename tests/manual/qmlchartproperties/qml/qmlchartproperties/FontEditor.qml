/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
