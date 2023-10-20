// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwidget.h"

#include <QApplication>
#include <QListView>
#include <QStringListModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;
    w.show();

    return a.exec();
}
