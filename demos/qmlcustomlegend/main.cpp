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

#include <QApplication>
#include <QtDeclarative/QDeclarativeEngine>
#include <QDir>
#include "qmlapplicationviewer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());
#ifdef Q_OS_ANDROID
    viewer->addImportPath(QString::fromLatin1("assets:/imports"));
    viewer->engine()->addPluginPath(QString::fromLatin1("%1/../%2").arg(QDir::homePath(), QString::fromLatin1("lib")));
#else
    viewer->addImportPath(QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), QString::fromLatin1("imports")));
#endif

    //viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setSource(QUrl("qrc:/qml/qmlcustomlegend/loader.qml"));
    viewer->setRenderHint(QPainter::Antialiasing, true);
    viewer->showExpanded();

    return app->exec();
}
