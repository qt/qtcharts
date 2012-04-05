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

#include "qchartview.h"
#include "qchart_p.h"
#include "qchartview_p.h"
#include <QGraphicsScene>
#include <QRubberBand>


/*!
    \enum QChartView::RubberBandPolicy

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
    QGraphicsScene to work. It manages the graphical representation of different types of
    QChartSeries and other chart related objects like QChartAxis and QChartLegend. If you want to
    display a chart in your existing QGraphicsScene, you can use the QChart class instead.

    \sa QChart
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs a chartView object which is a child of a\a parent.
*/
QChartView::QChartView(QChart *chart,QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new QChartViewPrivate())
{
    Q_ASSERT(chart);
    d_ptr->m_scene = new QGraphicsScene(this);
    d_ptr->m_chart = chart;
    setFrameShape(QFrame::NoFrame);
    setBackgroundRole(QPalette::Window);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(d_ptr->m_scene);
    d_ptr->m_scene->addItem(chart);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


/*!
    Destroys the object and it's children, like QChartSeries and QChartAxis object added to it.
*/
QChartView::~QChartView()
{
}

/*!
    Returns the pointer to the associated chart
*/
QChart* QChartView::chart() const
{
    return d_ptr->m_chart;
}

/*!
    Sets the RubberBandPlicy to \a rubberBand. Selected policy determines the way zooming is performed.
*/
void QChartView::setRubberBand(const RubberBands& rubberBand)
{
    d_ptr->m_rubberBandFlags=rubberBand;

    if (!d_ptr->m_rubberBandFlags) {
        delete d_ptr->m_rubberBand;
        d_ptr->m_rubberBand=0;
        return;
    }

    if (!d_ptr->m_rubberBand) {
        d_ptr->m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        d_ptr->m_rubberBand->setEnabled(true);
    }
}

/*!
    Returns the RubberBandPolicy that is currently being used by the widget.
*/
QChartView::RubberBands QChartView::rubberBand() const
{
    return d_ptr->m_rubberBandFlags;
}

/*!
    If Left mouse button is pressed and the RubberBandPolicy is enabled the \a event is accepted and the rubber band is displayed on the screen allowing the user to select the zoom area.
    If different mouse button is pressed and/or the RubberBandPolicy is disabled then the \a event is passed to QGraphicsView::mousePressEvent() implementation.
*/
void QChartView::mousePressEvent(QMouseEvent *event)
{
    if(d_ptr->m_rubberBand && d_ptr->m_rubberBand->isEnabled() && event->button() == Qt::LeftButton) {

        int padding = d_ptr->m_chart->margins().top();
        QRect rect(padding, padding, width() - 2 * padding, height() - 2 * padding);

        if (rect.contains(event->pos())) {
            d_ptr->m_rubberBandOrigin = event->pos();
            d_ptr->m_rubberBand->setGeometry(QRect(d_ptr->m_rubberBandOrigin, QSize()));
            d_ptr->m_rubberBand->show();
            event->accept();
        }
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}

/*!
    If RubberBand rectange specification has been initiated in pressEvent then \a event data is used to update RubberBand geometry.
    In other case the defualt QGraphicsView::mouseMoveEvent implementation is called.
*/
void QChartView::mouseMoveEvent(QMouseEvent *event)
{
    if(d_ptr->m_rubberBand && d_ptr->m_rubberBand->isVisible()) {
        QRectF margins = d_ptr->m_chart->margins();
        QRectF geometry = d_ptr->m_chart->geometry();
        QRectF rect =geometry.adjusted(margins.left(),margins.top(),-margins.right(),-margins.bottom());
        int width = event->pos().x() - d_ptr->m_rubberBandOrigin.x();
        int height = event->pos().y() - d_ptr->m_rubberBandOrigin.y();
        if (!d_ptr->m_rubberBandFlags.testFlag(VerticalRubberBand)) {
            d_ptr->m_rubberBandOrigin.setY(rect.top());
            height = rect.height();
        }
        if (!d_ptr->m_rubberBandFlags.testFlag(HorizonalRubberBand)) {
            d_ptr->m_rubberBandOrigin.setX(rect.left());
            width= rect.width();
        }
        d_ptr->m_rubberBand->setGeometry(QRect(d_ptr->m_rubberBandOrigin.x(),d_ptr->m_rubberBandOrigin.y(), width,height).normalized());
    }
    else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

/*!
    If left mouse button is release and RubberBand is enabled then \a event is accepted and the view is zoomed in to rect specified by RubberBand
    If it is the right mouse button \a event then RubberBand is dissmissed and zoom is canceled.
*/
void QChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(d_ptr->m_rubberBand) {
        if (event->button() == Qt::LeftButton && d_ptr->m_rubberBand->isVisible()) {
            d_ptr->m_rubberBand->hide();
            QRect rect = d_ptr->m_rubberBand->geometry();
            d_ptr->m_chart->zoomIn(rect);
            event->accept();
        }

        if(event->button()==Qt::RightButton){
            d_ptr->m_chart->zoomOut();
            event->accept();
        }
    }
    else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

/*!
    Pressing + and - keys performs zoomIn() and zoomOut() respectivly.
    In other \a event is passed to the QGraphicsView::keyPressEvent() implementation
*/
void QChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Plus:
            d_ptr->m_chart->zoomIn();
            break;
        case Qt::Key_Minus:
            d_ptr->m_chart->zoomOut();
            break;
        case Qt::Key_Left:
            d_ptr->m_chart->scrollLeft();
            break;
        case Qt::Key_Right:
            d_ptr->m_chart->scrollRight();
            break;
        case Qt::Key_Up:
            d_ptr->m_chart->scrollUp();
            break;
        case Qt::Key_Down:
            d_ptr->m_chart->scrollDown();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            break;
    }
}

/*!
    Resizes and updates the chart area using the \a event data
*/
void QChartView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    d_ptr->m_chart->resize(size());
    setSceneRect(d_ptr->m_chart->geometry());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QChartViewPrivate::QChartViewPrivate():
m_scene(0),
m_chart(0),
m_presenter(0),
m_rubberBand(0),
m_rubberBandFlags(QChartView::NoRubberBand)
{

}

QChartViewPrivate::~QChartViewPrivate()
{

}

#include "moc_qchartview.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
