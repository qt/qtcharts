// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtCharts

AreaSeries {
    id: series

    Behavior on opacity {
        NumberAnimation { duration: 250 }
    }
}
