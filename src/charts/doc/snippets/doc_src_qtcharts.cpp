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

//! [0]
#include <QtCharts>

using namespace QtCharts;
//! [0]

//! [1]
qmake CONFIG+=static
make
make install
//! [1]

//! [2]
qmake
make
./qmlpolarchart
//! [2]

//! [3]
QLineSeries* series = new QLineSeries();
series->append(0, 6);
series->append(2, 4);
...
chartView->chart()->addSeries(series);
chartView->chart()->createDefaultAxes();
//! [3]
