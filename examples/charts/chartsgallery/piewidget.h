// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef PIEWIDGET_H
#define PIEWIDGET_H

#include "contentwidget.h"

class PieWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit PieWidget(QWidget *parent = nullptr);
};

#endif
