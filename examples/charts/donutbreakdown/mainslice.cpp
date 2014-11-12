/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "mainslice.h"

QT_CHARTS_USE_NAMESPACE

//![1]
MainSlice::MainSlice(QPieSeries *breakdownSeries, QObject *parent)
    : QPieSlice(parent),
      m_breakdownSeries(breakdownSeries)
{
    connect(this, SIGNAL(percentageChanged()), this, SLOT(updateLabel()));
}
//![1]

QPieSeries *MainSlice::breakdownSeries() const
{
    return m_breakdownSeries;
}

void MainSlice::setName(QString name)
{
    m_name = name;
}

QString MainSlice::name() const
{
    return m_name;
}

//![2]
void MainSlice::updateLabel()
{
    this->setLabel(QString("%1 %2%").arg(m_name).arg(percentage() * 100, 0, 'f', 2));
}
//![2]

#include "moc_mainslice.cpp"

