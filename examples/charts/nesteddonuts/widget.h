// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QPieSeries>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void updateRotation();
    void explodeSlice(bool exploded);

private:
    QList<QPieSeries *> m_donuts;
    QTimer *updateTimer;
};

#endif // WIDGET_H
