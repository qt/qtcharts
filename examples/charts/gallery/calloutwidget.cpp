// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "calloutview.h"
#include "calloutwidget.h"

CalloutWidget::CalloutWidget(QWidget *parent)
    : ContentWidget(parent)
{
    // To make mouse tracking work, we need to subclass the QGraphicsView instead of just having
    // it as member of this class
    m_view = new CalloutView(this);
    m_view->resize(size());
}

void CalloutWidget::resizeEvent(QResizeEvent *)
{
    m_view->resize(size());
}
