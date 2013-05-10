/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "qchartview.h"
#include "qchartview_p.h"
#include "qchart_p.h"
#include <QGraphicsScene>
#include <QRubberBand>
#include <qmath.h>

/*!
    \enum QChartView::RubberBand

    This enum describes the different types of rubber bands that can be used for zoom rect selection

    \value NoRubberBand
    \value VerticalRubberBand
    \value HorizonalRubberBand
    \value RectangleRubberBand
*/

/*!
    \class QChartView
    \brief Standalone charting widget.

    QChartView is a standalone widget that can display charts. It does not require separate
    QGraphicsScene to work. If you want to display a chart in your existing QGraphicsScene,
    you need to use the QChart (or QPolarChart) class instead.

    \sa QChart, QPolarChart
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs a chartView object with parent \a parent.
*/

QChartView::QChartView(QWidget *parent)
    : QGraphicsView(parent),
      d_ptr(new QChartViewPrivate(this))
{

}

/*!
    Constructs a chartview object with parent \a parent to display a \a chart.
    Ownership of the \a chart is passed to chartview.
*/

QChartView::QChartView(QChart *chart, QWidget *parent)
    : QGraphicsView(parent),
      d_ptr(new QChartViewPrivate(this, chart))
{

}


/*!
    Destroys the chartview object and the associated chart.
*/
QChartView::~QChartView()
{
}

/*!
    Returns the pointer to the associated chart.
*/
QChart *QChartView::chart() const
{
    return d_ptr->m_chart;
}

/*!
    Sets the current chart to \a chart. Ownership of the new chart is passed to chartview
    and ownership of the previous chart is released.

    To avoid memory leaks users need to make sure the previous chart is deleted.
*/

void QChartView::setChart(QChart *chart)
{
    d_ptr->setChart(chart);
}

/*!
    Sets the rubber band flags to \a rubberBand.
    Selected flags determine the way zooming is performed.

    \note Rubber band zooming is not supported for polar charts.
*/
void QChartView::setRubberBand(const RubberBands &rubberBand)
{
    d_ptr->m_rubberBandFlags = rubberBand;

    if (!d_ptr->m_rubberBandFlags) {
        delete d_ptr->m_rubberBand;
        d_ptr->m_rubberBand = 0;
        return;
    }

    if (!d_ptr->m_rubberBand) {
        d_ptr->m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        d_ptr->m_rubberBand->setEnabled(true);
    }
}

/*!
    Returns the rubber band flags that are currently being used by the widget.
*/
QChartView::RubberBands QChartView::rubberBand() const
{
    return d_ptr->m_rubberBandFlags;
}

/*!
    If Left mouse button is pressed and the rubber band is enabled the \a event is accepted and the rubber band is displayed on the screen allowing the user to select the zoom area.
    If different mouse button is pressed and/or the rubber band is disabled then the \a event is passed to QGraphicsView::mousePressEvent() implementation.
*/
void QChartView::mousePressEvent(QMouseEvent *event)
{
    if (d_ptr->m_rubberBand && d_ptr->m_rubberBand->isEnabled() && event->button() == Qt::LeftButton) {

        QRectF plotArea = d_ptr->m_chart->plotArea();

        if (plotArea.contains(event->pos())) {
            d_ptr->m_rubberBandOrigin = event->pos();
            d_ptr->m_rubberBand->setGeometry(QRect(d_ptr->m_rubberBandOrigin, QSize()));
            d_ptr->m_rubberBand->show();
            event->accept();
        }
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

/*!
    If the rubber band rectange has been displayed in pressEvent then \a event data is used to update the rubber band geometry.
    Otherwise the default QGraphicsView::mouseMoveEvent implementation is called.
*/
void QChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (d_ptr->m_rubberBand && d_ptr->m_rubberBand->isVisible()) {
        QRect rect = d_ptr->m_chart->plotArea().toRect();
        int width = event->pos().x() - d_ptr->m_rubberBandOrigin.x();
        int height = event->pos().y() - d_ptr->m_rubberBandOrigin.y();
        if (!d_ptr->m_rubberBandFlags.testFlag(VerticalRubberBand)) {
            d_ptr->m_rubberBandOrigin.setY(rect.top());
            height = rect.height();
        }
        if (!d_ptr->m_rubberBandFlags.testFlag(HorizonalRubberBand)) {
            d_ptr->m_rubberBandOrigin.setX(rect.left());
            width = rect.width();
        }
        d_ptr->m_rubberBand->setGeometry(QRect(d_ptr->m_rubberBandOrigin.x(), d_ptr->m_rubberBandOrigin.y(), width, height).normalized());
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

/*!
    If left mouse button is released and the rubber band is enabled then \a event is accepted and
    the view is zoomed into the rect specified by the rubber band.
    If it is a right mouse button \a event then the rubber band is dismissed and the zoom is canceled.
*/
void QChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (d_ptr->m_rubberBand) {
        if (event->button() == Qt::LeftButton && d_ptr->m_rubberBand->isVisible()) {
            d_ptr->m_rubberBand->hide();
            QRectF rect = d_ptr->m_rubberBand->geometry();
            // Since plotArea uses QRectF and rubberband uses QRect, we can't just blindly use
            // rubberband's dimensions for vertical and horizontal rubberbands, where one
            // dimension must match the corresponding plotArea dimension exactly.
            if (d_ptr->m_rubberBandFlags == VerticalRubberBand) {
                rect.setX(d_ptr->m_chart->plotArea().x());
                rect.setWidth(d_ptr->m_chart->plotArea().width());
            } else if (d_ptr->m_rubberBandFlags == HorizonalRubberBand) {
                rect.setY(d_ptr->m_chart->plotArea().y());
                rect.setHeight(d_ptr->m_chart->plotArea().height());
            }
            d_ptr->m_chart->zoomIn(rect);
            event->accept();
        }

        if (event->button() == Qt::RightButton) {
            d_ptr->m_chart->zoomOut();
            event->accept();
        }
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

/*!
    Resizes and updates the chart area using the \a event data
*/
void QChartView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    d_ptr->resize();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QChartViewPrivate::QChartViewPrivate(QChartView *q, QChart *chart)
    : q_ptr(q),
      m_scene(new QGraphicsScene(q)),
      m_chart(chart),
      m_rubberBand(0),
      m_rubberBandFlags(QChartView::NoRubberBand)
{
    q_ptr->setFrameShape(QFrame::NoFrame);
    q_ptr->setBackgroundRole(QPalette::Window);
    q_ptr->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q_ptr->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q_ptr->setScene(m_scene);
    q_ptr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (!m_chart)
        m_chart = new QChart();
    m_scene->addItem(m_chart);
}

QChartViewPrivate::~QChartViewPrivate()
{
}

void QChartViewPrivate::setChart(QChart *chart)
{
    Q_ASSERT(chart);

    if (m_chart == chart)
        return;

    if (m_chart)
        m_scene->removeItem(m_chart);

    m_chart = chart;
    m_scene->addItem(m_chart);

    resize();
}

const qreal rad2deg(57.2957795);

void QChartViewPrivate::resize()
{
    // Flip chart width and height if the view has been rotated
    // more than 45 degrees from the horizontal so it fits better into the view.
    qreal angle = qAcos(q_ptr->transform().m11()) * rad2deg;
    QSize chartSize = q_ptr->size();

    if (angle > 45.0 && angle < 135.0) {
        chartSize.setHeight(q_ptr->size().width());
        chartSize.setWidth(q_ptr->size().height());
    }

    m_chart->resize(chartSize);
    q_ptr->setMinimumSize(m_chart->minimumSize().toSize());
    q_ptr->setSceneRect(m_chart->geometry());
}

#include "moc_qchartview.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
