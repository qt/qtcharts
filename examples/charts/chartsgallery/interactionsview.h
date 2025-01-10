// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef INTERACTIONSVIEW_H
#define INTERACTIONSVIEW_H

#include <QChartView>
#include <QPoint>

class InteractionsChart;

class InteractionsView : public QChartView
{
public:
    InteractionsView(InteractionsChart *chart, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    InteractionsChart *m_chart = nullptr;
    QPoint m_mousePos;
};

#endif
