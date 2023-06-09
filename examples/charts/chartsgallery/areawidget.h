// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef AREAWIDGET_H
#define AREAWIDGET_H

#include "contentwidget.h"

class AreaWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit AreaWidget(QWidget *parent = nullptr);
};

#endif
