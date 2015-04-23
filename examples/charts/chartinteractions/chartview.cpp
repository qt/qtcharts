/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

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
