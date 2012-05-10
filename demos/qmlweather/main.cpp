/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QDeclarativeContext>
#include <QDebug>
#include "qmlapplicationviewer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    QString appKey;
    if (argc > 1) {
        appKey = argv[1];
        qDebug() << "App key for worldweatheronline.com:" << appKey;
    } else {
        qWarning() << "No app key for worldweatheronline.com given. Using static test data instead of live data.";
    }
    viewer.rootContext()->setContextProperty("weatherAppKey", appKey);
    viewer.setSource(QUrl("qrc:/qml/qmlweather/main.qml"));
    viewer.showExpanded();
    return app->exec();
}
