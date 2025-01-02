// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartanimation_p.h>

QT_BEGIN_NAMESPACE

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

QT_END_NAMESPACE


