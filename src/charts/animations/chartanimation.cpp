/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

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


