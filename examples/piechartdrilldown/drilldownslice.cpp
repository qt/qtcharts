/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "drilldownslice.h"

QTCOMMERCIALCHART_USE_NAMESPACE

DrilldownSlice::DrilldownSlice(qreal value, QString prefix, QSeries* drilldownSeries)
    :m_drilldownSeries(drilldownSeries),
    m_prefix(prefix)
{
    setValue(value);
    setLabelVisible(true);
    updateLabel();
    connect(this, SIGNAL(changed()), this, SLOT(updateLabel()));
}

DrilldownSlice::~DrilldownSlice()
{

}

QSeries* DrilldownSlice::drilldownSeries() const
{
    return m_drilldownSeries;
}

void DrilldownSlice::updateLabel()
{
    QString label = m_prefix;
    label += " ";
    label += QString::number(this->value());
    label += "e, ";
    label += QString::number(this->percentage()*100, 'f', 1);
    label += "%";
    setLabel(label);
}

#include "moc_drilldownslice.cpp"
