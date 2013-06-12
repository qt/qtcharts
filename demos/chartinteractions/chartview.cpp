/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartview.h"
#include <QMouseEvent>
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
