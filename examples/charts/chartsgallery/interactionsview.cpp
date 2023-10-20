// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "interactionschart.h"
#include "interactionsview.h"

#include <QMouseEvent>

InteractionsView::InteractionsView(InteractionsChart *chart, QWidget *parent) :
    QChartView(chart, parent)
{
    m_chart = chart;
}

void InteractionsView::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();
    QChartView::mousePressEvent(event);
}

void InteractionsView::mouseMoveEvent(QMouseEvent *event)
{
    m_chart->handlePointMove(event->pos());
    QChartView::mouseMoveEvent(event);
}

void InteractionsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->pos() != m_mousePos) {
        m_chart->handlePointMove(event->pos());
        m_chart->setPointClicked(false);
    }
    QChartView::mouseReleaseEvent(event);
}
