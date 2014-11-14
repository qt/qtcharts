/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QCHARTSPLUGIN_H
#define QCHARTSPLUGIN_H

#include <QtDesigner/QDesignerCustomWidgetInterface>

class QChartsPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    QChartsPlugin(QObject *parent = 0);
    ~QChartsPlugin();

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
    QString domXml() const;
};

#endif /* QCHARTSPLUGIN_H */
