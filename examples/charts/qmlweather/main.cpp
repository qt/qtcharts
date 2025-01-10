// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

int main(int argc, char *argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
    QApplication app(argc, argv);

    QQuickView viewer;
    // The following are needed to make examples run without having to install the module
    // in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
                                      QString::fromLatin1("qml")));
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    QString appKey;
    if (argc > 1) {
        appKey = argv[1];
        qDebug() << "App key for worldweatheronline.com:" << appKey;
    } else {
        qWarning() << "No app key for worldweatheronline.com given. Using static test data instead of live data.";
    }
    viewer.setTitle(QStringLiteral("QML Weather"));
    viewer.rootContext()->setContextProperty("weatherAppKey", appKey);
    viewer.setSource(QUrl("qrc:/qml/qmlweather/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

    return app.exec();
}
