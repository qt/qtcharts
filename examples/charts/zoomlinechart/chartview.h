// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QRubberBand>

//![1]
class ChartView : public QChartView
//![1]
{
public:
    ChartView(QChart *chart, QWidget *parent = nullptr);

//![2]
protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
//![2]

private:
    bool m_isTouching = false;
};

#endif
