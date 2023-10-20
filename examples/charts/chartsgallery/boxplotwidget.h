// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef BOXPLOTWIDGET_H
#define BOXPLOTWIDGET_H

#include "contentwidget.h"

class BoxPlotWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit BoxPlotWidget(QWidget *parent = nullptr);

protected:
    bool doLoad() override;
};

#endif
