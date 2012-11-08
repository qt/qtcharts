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
#include <QtDeclarative>
#include <QtDeclarative/QDeclarativeEngine>
#include <QAbstractItemModel>
#include "declarativemodel.h"
#include "customtablemodel.h"
#include "qmlapplicationviewer.h"

const char *uri = "QmlCustomModel";

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    // @uri QmlCustomModel
    qmlRegisterUncreatableType<QAbstractItemModel>(uri, 1, 0, "AbstractItemModel",
                                                   QLatin1String("Trying to create uncreatable: AbstractItemModel."));
    qmlRegisterType<DeclarativeTableModel>(uri, 1, 0, "CustomModel");
    qmlRegisterType<DeclarativeTableModelElement>(uri, 1, 0, "CustomModelElement");

    // // viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setSource(QUrl("qrc:/qml/qmlcustommodel/loader.qml"));
    viewer->setRenderHint(QPainter::Antialiasing, true);
    viewer->showExpanded();

    return app->exec();
}
