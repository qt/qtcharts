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

#include "qlegend.h"
#include "qchart_p.h"
#include "qseries.h"
#include "legendmarker_p.h"
#include "qxyseries.h"
#include "qlineseries.h"
#include "qareaseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qbarset.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QPen>
#include <QTimer>

#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QLegend
    \brief part of QtCommercial chart API.

    QLegend is a graphical object, whics displays legend of the chart. Legend state is updated by QChart, when
    series have been changed. By default, legend is drawn by QChart, but user can set a new parent to legend and
    handle the drawing manually.
    User isn't supposed to create or delete legend objects, but can reference it via QChart class.

    \mainclass

    \sa QChart, QSeries
*/

/*!
    \enum QLegend::Layout

    This enum describes the possible position for legend inside chart.

    \value LayoutTop
    \value LayoutBottom
    \value LayoutLeft
    \value LayoutRight
*/


/*!
    \fn void QLegend::clicked(QSeries* series, Qt::MouseButton button)
    \brief Notifies when series has been clicked on legend \a series \a button
*/

/*!
    \fn void QLegend::clicked(QBarSet* barset, Qt::MouseButton button)
    \brief Notifies when barset has been clicked on legend \a barset \a button
*/

/*!
    \fn void QLegend::clicked(QPieSlice* slice, Qt::MouseButton button)
    \brief Notifies when pie slice has been clicked on legend \a slice \a button
*/

/*!
    Constructs the legend object and sets the parent to \a parent
*/

QLegend::QLegend(QChart *chart):QGraphicsWidget(chart),
    m_margin(5),
    m_offsetX(0),
    m_offsetY(0),
    m_brush(Qt::darkGray),              // TODO: default should come from theme
    m_alignment(QLegend::AlignmentTop),
    m_markers(new QGraphicsItemGroup(this)),
    m_attachedToChart(true),
    m_chart(chart),
    m_minWidth(0),
    m_minHeight(0),
    m_width(0),
    m_height(0),
    m_visible(false),
    m_dirty(false)
{
    setZValue(ChartPresenter::LegendZValue);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);
}

/*!
    Paints the legend to given \a painter. Paremeters \a option and \a widget arent used.
*/

void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	if(!m_visible) return;

    painter->setOpacity(opacity());
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(boundingRect());
}

/*!
    Bounding rect of legend.
*/

QRectF QLegend::boundingRect() const
{
    return m_rect;
}

/*!
    Sets the \a brush of legend. Brush affects the background of legend.
*/
void QLegend::setBrush(const QBrush &brush)
{
    if (m_brush != brush) {
        m_brush = brush;
        update();
    }
}

/*!
    Returns the brush used by legend.
*/
QBrush QLegend::brush() const
{
    return m_brush;
}

/*!
    Sets the \a pen of legend. Pen affects the legend borders.
*/
void QLegend::setPen(const QPen &pen)
{
    if (m_pen != pen) {
        m_pen = pen;
        update();
    }
}

/*!
    Returns the pen used by legend
*/

QPen QLegend::pen() const
{
    return m_pen;
}

/*!
    Sets the \a preferred layout for legend. Legend tries to paint itself on the defined position in chart.
    \sa QLegend::Layout
*/
void QLegend::setAlignmnent(QLegend::Alignments alignment)
{
    if(m_alignment!=alignment && m_attachedToChart) {
        m_alignment = alignment;
        updateLayout();
    }
}

/*!
    Returns the preferred layout for legend
*/
QLegend::Alignments QLegend::alignment() const
{
    return m_alignment;
}

/*!
    \internal \a series \a domain Should be called when series is added to chart.
*/
void QLegend::handleSeriesAdded(QSeries *series, Domain *domain)
{
    Q_UNUSED(domain)

    switch (series->type())
    {
    case QSeries::SeriesTypeLine: {
        QLineSeries *lineSeries = static_cast<QLineSeries *>(series);
        appendMarkers(lineSeries);
        break;
    }
    case QSeries::SeriesTypeArea: {
        QAreaSeries *areaSeries = static_cast<QAreaSeries *>(series);
        appendMarkers(areaSeries);
        break;
    }
    case QSeries::SeriesTypeBar: {
        QBarSeries *barSeries = static_cast<QBarSeries *>(series);
        appendMarkers(barSeries);
        break;
    }
    case QSeries::SeriesTypeStackedBar: {
        QStackedBarSeries *stackedBarSeries = static_cast<QStackedBarSeries *>(series);
        appendMarkers(stackedBarSeries);
        break;
    }
    case QSeries::SeriesTypePercentBar: {
        QPercentBarSeries *percentBarSeries = static_cast<QPercentBarSeries *>(series);
        appendMarkers(percentBarSeries);
        break;
    }
    case QSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = static_cast<QScatterSeries *>(series);
        appendMarkers(scatterSeries);
        break;
    }
    case QSeries::SeriesTypePie: {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        appendMarkers(pieSeries);
        connect(pieSeries,SIGNAL(added(QList<QPieSlice*>)),this,SLOT(handleAdded(QList<QPieSlice*>)));
        break;
    }
    case QSeries::SeriesTypeSpline: {
        QSplineSeries *splineSeries = static_cast<QSplineSeries *>(series);
        appendMarkers(splineSeries);
        break;
    }
    default: {
        qWarning()<< "QLegend::handleSeriesAdded" << series->type() << "unknown series type.";
        break;
    }
    }

   // wait for all series added
   if(!m_dirty){
	   QTimer::singleShot(0,this,SLOT(updateLayout()));
	   m_dirty=true;
   }
}

/*!
    \internal \a series Should be called when series is removed from chart.
*/
void QLegend::handleSeriesRemoved(QSeries *series)
{
    switch (series->type())
    {
    case QSeries::SeriesTypeArea: {
        QAreaSeries *areaSeries = static_cast<QAreaSeries *>(series);
        deleteMarkers(areaSeries);
        break;
    }
    case QSeries::SeriesTypePie: {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        disconnect(pieSeries, SIGNAL(added(QList<QPieSlice *>)), this, SLOT(handleAdded(QList<QPieSlice *>)));
        deleteMarkers(series);
        break;
    }
    default: {
        // All other types
        deleteMarkers(series);
        break;
    }
    }

    updateLayout();
}

/*!
    \internal \a slices Should be called when slices are added to pie chart.
*/
void QLegend::handleAdded(QList<QPieSlice *> slices)
{
    QPieSeries* series = static_cast<QPieSeries *> (sender());
    foreach(QPieSlice* slice, slices) {
        PieLegendMarker* marker = new PieLegendMarker(series,slice, this);
        m_markers->addToGroup(marker);
    }
    updateLayout();
}

/*!
    \internal \a slices Should be called when slices are removed from pie chart. Currently unused,
    because removed slices are also deleted and we listen destroyed signal
*/
void QLegend::handleRemoved(QList<QPieSlice *> slices)
{
    Q_UNUSED(slices)
}

/*!
    Detaches the legend from chart. Chart won't change layout of the legend.
*/
void QLegend::detachFromChart()
{
    m_attachedToChart = false;
}

/*!
    Attaches the legend to chart. Chart may change layout of the legend.
*/
void QLegend::attachToChart()
{
    m_attachedToChart = true;
}

/*!
    Returns true, if legend is attached to chart.
*/
bool QLegend::isAttachedToChart()
{
    return m_attachedToChart;
}

/*!
    \internal Helper function. Appends markers from \a series to legend.
*/
void QLegend::appendMarkers(QAreaSeries* series)
{
    AreaLegendMarker* marker = new AreaLegendMarker(series,this);
    m_markers->addToGroup(marker);
}

/*!
    \internal Helper function. Appends markers from \a series to legend.
*/
void QLegend::appendMarkers(QXYSeries* series)
{
    XYLegendMarker* marker = new XYLegendMarker(series,this);
    m_markers->addToGroup(marker);
}

/*!
    \internal Helper function. Appends markers from \a series to legend.
*/
void QLegend::appendMarkers(QBarSeries *series)
{
    foreach(QBarSet* set, series->barSets()) {
        BarLegendMarker* marker = new BarLegendMarker(series,set, this);
        m_markers->addToGroup(marker);
    }
}

/*!
    \internal Helper function. Appends markers from \a series to legend.
*/
void QLegend::appendMarkers(QPieSeries *series)
{
    foreach(QPieSlice* slice, series->slices()) {
        PieLegendMarker* marker = new PieLegendMarker(series,slice, this);
        m_markers->addToGroup(marker);
    }
}

/*!
    \internal Deletes all markers that are created from \a series
*/
void QLegend::deleteMarkers(QSeries *series)
{
    // Search all markers that belong to given series and delete them.

    QList<QGraphicsItem *> items = m_markers->childItems();

    foreach (QGraphicsItem *markers, items) {
        LegendMarker *marker = static_cast<LegendMarker*>(markers);
        if (marker->series() == series) {
            delete marker;
        }
    }
}

/*!
    \internal Updates layout of legend. Tries to fit as many markers as possible up to the maximum size of legend.
    If items don't fit, sets the visibility of scroll buttons accordingly.
    Causes legend to be resized.
*/

void QLegend::setOffset(const QPointF& point)
{

    switch(m_alignment) {

        case AlignmentTop:
        case AlignmentBottom: {
            if(m_width<=m_rect.width()) return;

            if (point.x() != m_offsetX) {
                m_offsetX = qBound(0.0, point.x(), m_width - m_rect.width());
                m_markers->setPos(-m_offsetX,m_rect.top());
            }
            break;
        }
        case AlignmentLeft:
        case AlignmentRight: {

            if(m_height<=m_rect.height()) return;

            if (point.y() != m_offsetY) {
                m_offsetY = qBound(0.0, point.y(), m_height - m_rect.height());
                m_markers->setPos(m_rect.left(),-m_offsetY);
            }
            break;
        }
    }
}

QPointF QLegend::offset() const
{
    return QPointF(m_offsetX,m_offsetY);
}

// this function runs first to set min max values
void QLegend::updateLayout()
{
	m_dirty=false;
	m_offsetX=0;
    QList<QGraphicsItem *> items = m_markers->childItems();

    if(items.isEmpty()) return;

    m_minWidth=0;
    m_minHeight=0;

    switch(m_alignment) {

        case AlignmentTop:
        case AlignmentBottom: {
            QPointF point = m_rect.topLeft();
            m_width = 0;
            foreach (QGraphicsItem *item, items) {
                item->setPos(point.x(),m_rect.height()/2 -item->boundingRect().height()/2);
                const QRectF& rect = item->boundingRect();
                qreal w = rect.width();
                m_minWidth=qMax(m_minWidth,w);
                m_minHeight=qMax(m_minHeight,rect.height());
                m_width+=w;
                point.setX(point.x() + w);
            }
            if(m_width<m_rect.width()){
                m_markers->setPos(m_rect.width()/2-m_width/2,m_rect.top());
            }else{
                m_markers->setPos(m_rect.topLeft());
            }
            m_height=m_minHeight;
        }
        break;
        case AlignmentLeft:
        case AlignmentRight:{
            QPointF point = m_rect.topLeft();
            m_height = 0;
            foreach (QGraphicsItem *item, items) {
                item->setPos(point);
                const QRectF& rect = item->boundingRect();
                qreal h = rect.height();
                m_minWidth=qMax(m_minWidth,rect.width());
                m_minHeight=qMax(m_minHeight,h);
                m_height+=h;
                point.setY(point.y() + h);
            }
            if(m_height<m_rect.height()){
                m_markers->setPos(m_rect.left(),m_rect.height()/2-m_height/2);
            }else{
                m_markers->setPos(m_rect.topLeft());
            }
            m_width=m_minWidth;
        }
        break;
    }

    m_chart->d_ptr->m_presenter->updateLayout(); //TODO fixme;
}

void QLegend::setBackgroundVisible(bool visible)
{
    if(m_visible!=visible)
    {
    	m_visible=visible;
    	update();
    }
}

bool QLegend::isBackgroundVisible() const
{
   return m_visible;
}

void QLegend::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    const QRectF& rect = QRectF(QPoint(0,0),event->newSize());
    QGraphicsWidget::resizeEvent(event);
    if(m_rect != rect){
        m_rect = rect;
        updateLayout();
    }
}

void QLegend::hideEvent(QHideEvent *event)
{
    QGraphicsWidget::hideEvent(event);
    setEnabled(false);
    updateLayout();
}

void QLegend::showEvent(QShowEvent *event)
{
    QGraphicsWidget::showEvent(event);
    setEnabled(true);
    updateLayout();
}

#include "moc_qlegend.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
