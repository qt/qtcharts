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
    property variant series

    Button {
        text: "slice color"
        onClicked: series.at(0).color = main.nextColor();
    }
    Button {
        text: "slice border color"
        onClicked: series.at(0).borderColor = main.nextColor();
    }
    Button {
        text: "slice border width +"
        onClicked: series.at(0).borderWidth++;
    }
    Button {
        text: "slice border width -"
        onClicked: series.at(0).borderWidth--;
    }
    Button {
        text: "slice label visible"
        onClicked: series.at(0).labelVisible = !series.at(0).labelVisible;
    }
    Button {
        text: "slice label color"
        onClicked: series.at(0).labelColor = main.nextColor();
    }
    Button {
        text: "slice exploded"
        onClicked: series.at(0).exploded = !series.at(0).exploded;
    }
}
