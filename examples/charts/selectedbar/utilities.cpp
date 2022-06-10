// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
