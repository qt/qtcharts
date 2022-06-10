// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;
    w.setWindowTitle(QStringLiteral("Candlestick Chart Tester"));
    w.resize(1280, 720);
    w.show();

    return a.exec();
}
