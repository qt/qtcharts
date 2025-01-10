// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "donutbreakdownmainslice.h"

//![1]
DonutBreakdownMainSlice::DonutBreakdownMainSlice(QPieSeries *breakdownSeries, QObject *parent)
    : QPieSlice(parent),
      m_breakdownSeries(breakdownSeries)
{
    connect(this, &DonutBreakdownMainSlice::percentageChanged,
            this, &DonutBreakdownMainSlice::updateLabel);
}
//![1]

QPieSeries *DonutBreakdownMainSlice::breakdownSeries() const
{
    return m_breakdownSeries;
}

void DonutBreakdownMainSlice::setName(const QString &name)
{
    m_name = name;
}

QString DonutBreakdownMainSlice::name() const
{
    return m_name;
}

//![2]
void DonutBreakdownMainSlice::updateLabel()
{
    setLabel(QString("%1 %2%").arg(m_name).arg(percentage() * 100, 0, 'f', 2));
}
//![2]
