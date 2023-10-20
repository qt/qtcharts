// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef DYNAMICSPLINEWIDGET_H
#define DYNAMICSPLINEWIDGET_H

#include "contentwidget.h"

#include <QTimer>

QT_FORWARD_DECLARE_CLASS(QSplineSeries)
QT_FORWARD_DECLARE_CLASS(QValueAxis)

class DynamicSplineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit DynamicSplineWidget(QWidget *parent = nullptr);

public slots:
    void handleTimeout();

private:
    QSplineSeries *m_series = nullptr;
    QValueAxis *m_axisX = nullptr;
    QValueAxis *m_axisY = nullptr;
    QTimer m_timer;
    QStringList m_titles;
    qreal m_step = 0.;
    qreal m_x = 5;
    qreal m_y = 1;
};

#endif
