/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include <private/chartitem_p.h>
#include <private/qabstractseries_p.h>
#include <private/abstractdomain_p.h>
#include <QtGui/QPainter>

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
