// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef SELECTEDBARWIDGET_H
#define SELECTEDBARWIDGET_H

#include "contentwidget.h"

#include <QStringList>

QT_FORWARD_DECLARE_CLASS(QBarSet)

class SelectedBarWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit SelectedBarWidget(QWidget *parent = nullptr);

private:
    QBarSet *createChickenSet();
    QBarSet *createPorkSet();
    QBarSet *createTurkeySet();
    QBarSet *createHamSet();
    QStringList createYearCategories();
};

#endif
