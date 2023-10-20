// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CUSTOMCHARTWIDGET_H
#define CUSTOMCHARTWIDGET_H

#include "contentwidget.h"

class CustomChartWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit CustomChartWidget(QWidget *parent = nullptr);
};

#endif
