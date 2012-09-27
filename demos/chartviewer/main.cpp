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

#include "window.h"
#include <QApplication>
#include <QMainWindow>

QVariantHash parseArgs(QStringList args)
{
    QVariantHash parameters;

    while (!args.isEmpty()) {

        QString param = args.takeFirst();
        if (param.startsWith("--")) {
            param.remove(0, 2);

            if (args.isEmpty() || args.first().startsWith("--")) {
                parameters[param] = true;
            }
            else {

                QString value = args.takeFirst();
                if (value == "true" || value == "on" || value == "enabled") {
                    parameters[param] = true;
                }
                else if (value == "false" || value == "off" || value == "disable") {
                    parameters[param] = false;
                }
                else {
                    if(value.endsWith( '"' )) value.chop(1);
                    if(value.startsWith( '"' )) value.remove(0,1);
                    parameters[param] = value;
                }
            }
        }
    }

    return parameters;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVariantHash parameters = parseArgs(QApplication::arguments());
    Window window(parameters);
    window.show();
    return a.exec();
}

