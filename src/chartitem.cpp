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

#include "chartitem_p.h"
#include "qabstractseries_p.h"
#include "abstractdomain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartItem::ChartItem(QAbstractSeriesPrivate *series,QGraphicsItem* item):
      ChartElement(item),
      m_series(series)
{

}

QSharedPointer<AbstractDomain> ChartItem::domain() const
{
    return m_series->domain();
}

void ChartItem::handleDomainUpdated()
{
    qWarning() <<  __FUNCTION__<< "Slot not implemented";
}

#include "moc_chartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
