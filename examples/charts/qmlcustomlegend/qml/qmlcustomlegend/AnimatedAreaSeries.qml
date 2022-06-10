// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.0
import QtCharts 2.0

AreaSeries {
    id: series

    Behavior on opacity {
        NumberAnimation { duration: 250 }
    }
}
