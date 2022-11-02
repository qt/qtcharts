// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "chartwindow.h"

#include <QApplication>

//![1]
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartWindow mainWindow;
    mainWindow.resize(640, 480);
    mainWindow.show();
    return a.exec();
}
//![1]
