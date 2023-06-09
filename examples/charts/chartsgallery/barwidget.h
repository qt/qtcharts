// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef BARWIDGET_H
#define BARWIDGET_H

#include "contentwidget.h"

class BarWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit BarWidget(QWidget *parent = nullptr);
};

#endif
