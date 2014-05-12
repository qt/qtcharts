/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartanimation_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartAnimation::ChartAnimation(QObject *parent) :
    QVariantAnimation(parent),
    m_destructing(false)
{
}

void ChartAnimation::stopAndDestroyLater()
{
    m_destructing = true;
    stop();
    deleteLater();
}

void ChartAnimation::startChartAnimation()
{
    if (!m_destructing)
        start();
}

QTCOMMERCIALCHART_END_NAMESPACE


