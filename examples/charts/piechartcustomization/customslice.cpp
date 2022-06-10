// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "customslice.h"

QT_USE_NAMESPACE

CustomSlice::CustomSlice(QString label, qreal value)
    : QPieSlice(label, value)
{
    connect(this, &CustomSlice::hovered, this, &CustomSlice::showHighlight);
}

QBrush CustomSlice::originalBrush()
{
    return m_originalBrush;
}

void CustomSlice::showHighlight(bool show)
{
    if (show) {
        QBrush brush = this->brush();
        m_originalBrush = brush;
        brush.setColor(brush.color().lighter());
        setBrush(brush);
    } else {
        setBrush(m_originalBrush);
    }
}

#include "moc_customslice.cpp"
