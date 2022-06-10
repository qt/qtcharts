// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include "tablewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TableWidget w;
    w.show();
    return a.exec();
}
