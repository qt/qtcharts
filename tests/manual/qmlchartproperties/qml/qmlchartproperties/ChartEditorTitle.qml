// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0

Flow {
    property variant chart
    anchors.fill: parent
    flow: Flow.TopToBottom
    spacing: 5

    FontEditor {
        fontDescription: "title"
        function editedFont() {
            return chart.titleFont;
        }
    }
}
