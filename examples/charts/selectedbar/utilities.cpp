/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "utilities.h"
#include <QCoreApplication>

namespace Utilities
{

QBarSet *createChickenSet()
{
    QBarSet *set = new QBarSet(QCoreApplication::tr("Chicken"));
    set->append({15.0, 12.0, 8.0, 11.5, 13.7});
    return set;
}

QBarSet *createPorkSet()
{
    QBarSet *set = new QBarSet(QCoreApplication::tr("Pork"));
    set->append({9.0, 11.0, 9.0, 7, 12.2});
    return set;
}

QBarSet *createTurkeySet()
{
    QBarSet *set = new QBarSet(QCoreApplication::tr("Turkey"));
    set->append({5.0, 7.6, 9.3, 8, 8.1});
    return set;
}

QBarSet *createHamSet()
{
    QBarSet *set = new QBarSet(QCoreApplication::tr("Ham"));
    set->append({5.4, 7.1, 9.3, 12.3, 11.3});
    return set;
}

QStringList createYearCategories()
{
    return QStringList{QCoreApplication::tr("2017"),
                       QCoreApplication::tr("2018"),
                       QCoreApplication::tr("2019"),
                       QCoreApplication::tr("2020"),
                       QCoreApplication::tr("2021")};
}

}
