// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "pcccustomslice.h"

PccCustomSlice::PccCustomSlice(const QString &label, qreal value)
    : QPieSlice(label, value)
{
    connect(this, &PccCustomSlice::hovered, this, &PccCustomSlice::showHighlight);
}

QBrush PccCustomSlice::originalBrush()
{
    return m_originalBrush;
}

void PccCustomSlice::showHighlight(bool show)
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
