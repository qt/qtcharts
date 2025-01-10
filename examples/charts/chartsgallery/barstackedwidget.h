// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef BARSTACKEDWIDGET_H
#define BARSTACKEDWIDGET_H

#include "contentwidget.h"

class BarStackedWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit BarStackedWidget(QWidget *parent = nullptr);
};

#endif
