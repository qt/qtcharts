// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef POLARCHARTVIEW_H
#define POLARCHARTVIEW_H

#include <QChartView>

class PolarChartView : public QChartView
{
public:
    PolarChartView(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void switchChartType();
};

#endif
