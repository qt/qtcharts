/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
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

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent), m_rubberBand(QRubberBand::Rectangle, this), m_chart(chart)
{
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    m_origin = event->pos();
    m_rubberBand.setGeometry(QRect(m_origin, QSize()));
    m_rubberBand.show();

    event->accept();
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_rubberBand.isVisible())
        m_rubberBand.setGeometry(QRect(m_origin, event->pos()).normalized());
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_rubberBand.isVisible()) {
        m_rubberBand.hide();

        QRect rect = m_rubberBand.geometry();
        m_chart->zoomIn(rect);
        event->accept();
    }

    if (event->button() == Qt::RightButton) {
        m_chart->zoomOut();
    }
}

//![1]
void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        m_chart->zoomIn();
        break;
    case Qt::Key_Minus:
        m_chart->zoomOut();
        break;
//![1]
    case Qt::Key_Left:
        m_chart->scrollLeft();
        break;
    case Qt::Key_Right:
        m_chart->scrollRight();
        break;
    case Qt::Key_Up:
        m_chart->scrollUp();
        break;
    case Qt::Key_Down:
        m_chart->scrollDown();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
