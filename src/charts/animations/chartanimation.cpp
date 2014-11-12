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

#include <private/chartanimation_p.h>

QT_CHARTS_BEGIN_NAMESPACE

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

QT_CHARTS_END_NAMESPACE


