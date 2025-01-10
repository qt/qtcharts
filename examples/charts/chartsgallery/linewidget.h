// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

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
