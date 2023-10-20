// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "widget.h"

#include <QApplication>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();
    if (inputDevice.isNull()) {
        QMessageBox::warning(nullptr, "audio",
                             "There is no audio input device available.");
        return -1;
    }

    Widget w(inputDevice);
    w.resize(800, 600);
    w.show();
    
    return a.exec();
}
