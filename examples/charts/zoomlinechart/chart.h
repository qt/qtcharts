// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CHART_H
#define CHART_H

#include <QChart>

QT_FORWARD_DECLARE_CLASS(QGestureEvent)

//![1]
class Chart : public QChart
//![1]
{
public:
    explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});

protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);
};

#endif
