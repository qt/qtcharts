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

#include <private/chartitem_p.h>
#include <private/qabstractseries_p.h>
#include <private/abstractdomain_p.h>

QT_CHARTS_BEGIN_NAMESPACE

ChartItem::ChartItem(QAbstractSeriesPrivate *series,QGraphicsItem* item):
      ChartElement(item),
      m_validData(true),
      m_series(series)
{

}

AbstractDomain* ChartItem::domain() const
{
    return m_series->domain();
}

void ChartItem::handleDomainUpdated()
{
    qWarning() <<  __FUNCTION__<< "Slot not implemented";
}

#include "moc_chartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
