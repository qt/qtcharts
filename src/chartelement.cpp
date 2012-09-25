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

#include "chartelement_p.h"
#include "chartpresenter_p.h"
#include "domain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartElement::ChartElement(ChartPresenter *presenter)
    : QObject(presenter),
      m_presenter(presenter),
      m_domain(0)
{
}

void ChartElement::setPresenter(ChartPresenter *presenter)
{
    m_presenter = presenter;
}

ChartPresenter *ChartElement::presenter() const
{
    return m_presenter;
}

void ChartElement::setDomain(Domain *domain)
{
    m_domain = domain;
}

Domain *ChartElement::domain() const
{
    return m_domain;
}

void ChartElement::handleGeometryChanged(const QRectF &rect)
{
    Q_UNUSED(rect);
    qWarning() << "Slot not implemented";
}

void ChartElement::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    Q_UNUSED(minX);
    Q_UNUSED(maxX);
    Q_UNUSED(minY);
    Q_UNUSED(maxY);
    qWarning() << "Slot not implemented";
}

void ChartElement::handleDomainUpdated()
{
    qWarning() << "Slot not implemented";
}


#include "moc_chartelement_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
