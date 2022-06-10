// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef UTILITIES_H
#define UTILITIES_H

#include <QList>
#include <QBarSet>

namespace Utilities
{
    QBarSet *createChickenSet();
    QBarSet *createPorkSet();
    QBarSet *createTurkeySet();
    QBarSet *createHamSet();
    QStringList createYearCategories();
    qreal totalSum(const QList<QBarSet *> &setList);
}

#endif // UTILITIES_H
