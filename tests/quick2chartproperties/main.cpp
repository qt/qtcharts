/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets/QApplication>
#include <QtQuick/QQuickItem>
#include <QDir>
#include <QtQml/QQmlEngine>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
#ifdef Q_OS_ANDROID
    viewer.addImportPath(QString::fromLatin1("assets:/qml"));
    viewer.engine()->addPluginPath(QString::fromLatin1("%1/../%2").arg(QDir::homePath(), QString::fromLatin1("lib")));
#else
    viewer.addImportPath(QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), QString::fromLatin1("qml")));
#endif
    viewer.setSource(QUrl("qrc:/qml/quick2chartproperties/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
