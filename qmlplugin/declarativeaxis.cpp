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

#include "declarativeaxis.h"
#include "declarativechart.h"
#include <QAxis>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeAxis::DeclarativeAxis(QObject *parent) :
    QAxis(parent),
    m_role(DeclarativeAxis::RoleX)
{
}

void DeclarativeAxis::classBegin()
{
}

void DeclarativeAxis::componentComplete()
{
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());
    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(chart);
        QAxis *axis = 0;
        if (m_role == RoleX)
            axis = chart->axisX();
        else
            axis = chart->axisY();
        Q_ASSERT(axis);
        // TODO?
        //foreach(DeclarativeCategory catecory, categories());
        //axis->categories()->insert(0, "Jun");
//        axis->categories()->insert(1, "Jul");
//        axis->categories()->insert(2, "Aug");
//        axis->categories()->insert(3, "Sep");
//        axis->categories()->insert(4, "Oct");
//        axis->categories()->insert(5, "Nov");
        //axis->categories()->insert(6, "Dec");
    }
}

void DeclarativeAxis::setRole(AxisRole role)
{
    // TODO: apply the role to possible parent chart
    m_role = role;
}

#include "moc_declarativeaxis.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
