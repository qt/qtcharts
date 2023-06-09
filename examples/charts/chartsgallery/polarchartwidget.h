// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef POLARCHARTWIDGET_H
#define POLARCHARTWIDGET_H

#include "contentwidget.h"

class PolarChartView;

class PolarChartWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit PolarChartWidget(QWidget *parent = nullptr);
};

#endif
