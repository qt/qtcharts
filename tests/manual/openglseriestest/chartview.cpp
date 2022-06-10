// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "chartview.h"
#include <QtGui/QMouseEvent>

QT_USE_NAMESPACE

ChartView::ChartView(QWidget *parent) :
    QChartView(parent)
{
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-1.0, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(1.0, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 1.0);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -1.0);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
