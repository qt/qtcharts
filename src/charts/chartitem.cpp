// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartitem_p.h>
#include <private/qabstractseries_p.h>
#include <private/abstractdomain_p.h>
#include <QtGui/QPainter>

QT_BEGIN_NAMESPACE

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

void ChartItem::cleanup()
{
    disconnect();
}

void ChartItem::handleDomainUpdated()
{
    qWarning() <<  __FUNCTION__<< "Slot not implemented";
}

QT_END_NAMESPACE

#include "moc_chartitem_p.cpp"
