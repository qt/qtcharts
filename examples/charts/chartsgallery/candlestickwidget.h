// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CANDLESTICKWIDGET_H
#define CANDLESTICKWIDGET_H

#include "contentwidget.h"

class CandleStickWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit CandleStickWidget(QWidget *parent = nullptr);

protected:
    bool doLoad() override;
};

#endif
