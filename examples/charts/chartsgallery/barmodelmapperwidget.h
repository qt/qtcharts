// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef BARMODELMAPPERWIDGET_H
#define BARMODELMAPPERWIDGET_H

#include "contentwidget.h"

QT_FORWARD_DECLARE_CLASS(QChartView)

class BarModelMapperWidget : public ContentWidget
{
    Q_OBJECT
public:
    BarModelMapperWidget(QWidget *parent = nullptr);
};

#endif
