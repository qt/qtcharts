// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
