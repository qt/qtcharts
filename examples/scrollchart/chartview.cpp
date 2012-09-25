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
#include <QDebug>

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    m_isScrolling(false),
    m_rubberBand(QRubberBand::Rectangle, this)
{
    // setRubberBand(QChartView::RectangleRubberBand);
    this->chart()->setAnimationOptions(QChart::NoAnimation);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {

        QRectF rect = chart()->plotArea();

        m_origin = event->pos();

        if (!rect.contains(m_origin))
            return;

        m_rubberBand.setGeometry(QRect(m_origin, QSize()));
        m_rubberBand.show();
    }

    if (event->button() == Qt::LeftButton) {
        m_origin = event->pos();
        m_isScrolling = true;
    }

    event->accept();
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_rubberBand.isVisible())
        m_rubberBand.setGeometry(QRect(m_origin, event->pos()).normalized());

    if (m_isScrolling) {
        QPointF delta = m_origin - event->pos();
        chart()->scroll(delta.x(), -delta.y());
        m_origin = event->pos();
    }

}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && m_rubberBand.isVisible()) {
        m_rubberBand.hide();

        QRect rect = m_rubberBand.geometry();
        chart()->zoomIn(rect);
        event->accept();
    }

    if (event->button() == Qt::LeftButton) {
        m_isScrolling = false;
    }
}

//![1]
void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
//![1]
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
