// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "piedrilldownslice.h"

PieDrilldownSlice::PieDrilldownSlice(qreal value, const QString &prefix, QAbstractSeries *drilldownSeries)
    : m_drilldownSeries(drilldownSeries),
      m_prefix(prefix)
{
    setValue(value);
    updateLabel();
    setLabelFont(QFont("Arial", 8));
    connect(this, &PieDrilldownSlice::percentageChanged, this, &PieDrilldownSlice::updateLabel);
    connect(this, &PieDrilldownSlice::hovered, this, &PieDrilldownSlice::showHighlight);
}

QAbstractSeries *PieDrilldownSlice::drilldownSeries() const
{
    return m_drilldownSeries;
}

void PieDrilldownSlice::updateLabel()
{
    setLabel(QStringLiteral("%1 $%2, %3%").arg(m_prefix,
                                               QString::number(value()),
                                               QString::number(percentage() * 100, 'f', 1)));
}

void PieDrilldownSlice::showHighlight(bool show)
{
    setLabelVisible(show);
    setExploded(show);
}
