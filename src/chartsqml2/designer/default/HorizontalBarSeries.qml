/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

import QtQuick 2.0
import QtCharts 2.0


ChartView {
    width: 300
    height: 300

    HorizontalBarSeries {
        name: "HorizontalBarSeries"
        BarSet { label: "Set1"; values: [2, 2, 3] }
        BarSet { label: "Set2"; values: [5, 1, 2] }
        BarSet { label: "Set3"; values: [3, 5, 8] }
    }
}
