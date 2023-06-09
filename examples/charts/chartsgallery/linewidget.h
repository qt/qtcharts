// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include "contentwidget.h"

class LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit LineWidget(QWidget *parent = nullptr);
};

#endif
