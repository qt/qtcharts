/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

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
