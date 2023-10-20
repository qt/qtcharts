// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef NESTEDDONUTSWIDGET_H
#define NESTEDDONUTSWIDGET_H

#include "contentwidget.h"

QT_FORWARD_DECLARE_CLASS(QTimer)
QT_FORWARD_DECLARE_CLASS(QPieSeries)

class NestedDonutsWidget : public ContentWidget
{
    Q_OBJECT
public:
    NestedDonutsWidget(QWidget *parent = nullptr);

public slots:
    void updateRotation();
    void explodeSlice(bool exploded);

private:
    QList<QPieSeries *> m_donuts;
    QTimer *m_updateTimer = nullptr;
};

#endif
