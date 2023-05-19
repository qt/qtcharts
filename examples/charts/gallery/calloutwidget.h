// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CALLOUTWIDGET_H
#define CALLOUTWIDGET_H

#include "contentwidget.h"

class CalloutView;

class CalloutWidget : public ContentWidget
{
    Q_OBJECT
public:
    CalloutWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;

private:
    CalloutView *m_view;
};

#endif
