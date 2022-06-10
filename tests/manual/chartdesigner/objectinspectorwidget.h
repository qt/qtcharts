// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QtWidgets/QWidget>

class InspectorWidget : public QWidget
{
public:
    InspectorWidget();
    ~InspectorWidget();

private:
    QIcon getColorIcon(const QColor& color,const QSize &size) const;

};

#endif
