// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "chartview.h"
#include <QtGui/QMouseEvent>
#include "chart.h"

ChartView::ChartView(Chart *chart, QWidget *parent) :
    QChartView(chart, parent)
{
    m_chart = chart;
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();
    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    m_chart->handlePointMove(event->pos());
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->pos() != m_mousePos) {
        m_chart->handlePointMove(event->pos());
        m_chart->setPointClicked(false);
    }
    QChartView::mouseReleaseEvent(event);
}
