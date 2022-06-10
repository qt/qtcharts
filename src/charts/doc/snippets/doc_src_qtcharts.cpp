// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
