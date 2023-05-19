// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef STACKEDDRILLDOWNWIDGET_H
#define STACKEDDRILLDOWNWIDGET_H

#include "contentwidget.h"

class StackedDrilldownWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit StackedDrilldownWidget(QWidget *parent = nullptr);
};

#endif
