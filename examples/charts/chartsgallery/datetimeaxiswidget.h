// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef DATETIMEAXISWIDGET_H
#define DATETIMEAXISWIDGET_H

#include "contentwidget.h"

class DateTimeAxisWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit DateTimeAxisWidget(QWidget *parent = nullptr);

protected:
    bool doLoad() override;
};

#endif
