// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtCharts

AreaSeries {
    id: series

    Behavior on opacity {
        NumberAnimation { duration: 250 }
    }
}
