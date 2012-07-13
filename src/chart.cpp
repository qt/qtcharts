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

#include "chart_p.h"
#include "chartpresenter_p.h"
#include "domain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Chart::Chart(ChartPresenter *presenter):QObject(presenter),
    m_animator(0),
    m_presenter(presenter),
    m_domain(0)
{
}

void Chart::setAnimator(ChartAnimator* animator)
{
    m_animator=animator;
}

ChartAnimator* Chart::animator() const
{
    return m_animator;
}


void Chart::setPresenter(ChartPresenter *presenter)
{
    m_presenter=presenter;
}

ChartPresenter* Chart::presenter() const
{
    return m_presenter;
}

void Chart::setDomain(Domain *domain)
{
    m_domain=domain;
}

Domain* Chart::domain() const
{
    return m_domain;
}

void Chart::handleGeometryChanged(const QRectF& rect)
{
    Q_UNUSED(rect);
    qWarning()<<"Slot not implemented";
}

void Chart::handleDomainChanged(qreal minX,qreal maxX,qreal minY,qreal maxY)
{
    Q_UNUSED(minX);
    Q_UNUSED(maxX);
    Q_UNUSED(minY);
    Q_UNUSED(maxY);
    qWarning()<<"Slot not implemented";
}

void Chart::handleDomainUpdated()
{
    qWarning()<<"Slot not implemented";
}


#include "moc_chart_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
