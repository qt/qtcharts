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
#include "qlegend_p.h"
#include "qabstractseries.h"
#include "qabstractseries_p.h"
#include "qchart_p.h"
#include "legendlayout_p.h"
#include "qxyseries.h"
#include "qlineseries.h"
#include "qareaseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"
#include "qabstractbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qbarset.h"
#include "qpieseries.h"
#include "qpieseries_p.h"
#include "qpieslice.h"
#include "chartpresenter_p.h"
#include "chartlayout_p.h"
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QGraphicsSceneEvent>
#include <QGraphicsItemGroup>

#include "qlegendmarker.h"
#include "qlegendmarker_p.h"
#include "legendmarkeritem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QLegend
    \brief Legend object
    \mainclass

    QLegend is a graphical object, whics displays legend of the chart. Legend state is updated by QChart, when
    series have been changed. By default, legend is drawn by QChart, but user can set a new parent to legend and
    handle the drawing manually.
    User isn't supposed to create or delete legend objects, but can reference it via QChart class.

    \image examples_percentbarchart_legend.png

    \sa QChart
*/
/*!
    \qmlclass Legend QLegend
    \brief Legend is part of QtCommercial Chart QML API.

    Legend is a graphical object, whics displays legend of the chart. Legend state is updated by ChartView, when
    series have been changed. Legend is used via ChartView class. For example:
    \code
        ChartView {
            legend.visible: true
            legend.alignment: Qt.AlignBottom
            // Add a few series...
        }
    \endcode

    \image examples_percentbarchart_legend.png
*/

/*!
    \property QLegend::alignment
    \brief The alignment of the legend.

    Legend paints on the defined position in the chart. The following alignments are supported:
    Qt::AlignTop, Qt::AlignBottom, Qt::AlignLeft, Qt::AlignRight. If you set more than one flag the result is undefined.
*/
/*!
    \qmlproperty Qt.Alignment Legend::alignment
    \brief The alignment of the legend.

    Legend paints on the defined position in the chart. The following alignments are supported:
    Qt.AlignTop, Qt.AlignBottom, Qt.AlignLeft, Qt.AlignRight. If you set more than one flag the result is undefined.
*/

/*!
    \property QLegend::backgroundVisible
    Whether the legend background is visible or not.
*/
/*!
    \qmlproperty bool Legend::backgroundVisible
    Whether the legend background is visible or not.
*/

/*!
    \property QLegend::color
    The color of the legend, i.e. the background (brush) color. Note that if you change the color
    of the legend, the style of the legend brush is set to Qt::SolidPattern.
*/
/*!
    \qmlproperty color Legend::color
    The color of the legend, i.e. the background (brush) color.
*/

/*!
    \property QLegend::borderColor
    The border color of the legend, i.e. the line color.
*/
/*!
    \qmlproperty color Legend::borderColor
    The border color of the legend, i.e. the line color.
*/

/*!
    \property QLegend::font
    The font of markers used by legend
*/
/*!
    \qmlproperty Font Legend::font
    The font of markers used by legend
*/

/*!
    \property QLegend::labelColor
    The color of brush used to draw labels.
*/
/*!
    \qmlproperty color QLegend::labelColor
    The color of brush used to draw labels.
*/

/*!
    \fn void QLegend::backgroundVisibleChanged(bool)
    The visibility of the legend background changed to \a visible.
*/

/*!
    \fn void QLegend::colorChanged(QColor)
    The color of the legend background changed to \a color.
*/

/*!
    \fn void QLegend::borderColorChanged(QColor)
    The border color of the legend background changed to \a color.
*/

/*!
    \fn void QLegend::fontChanged(QFont)
    The font of markers of the legend changed to \a font.
*/

/*!
    \fn void QLegend::labelColorChanged(QColor color)
    This signal is emitted when the color of brush used to draw labels has changed to \a color.
*/

/*!
 Constructs the legend object and sets the parent to \a parent
 */

QLegend::QLegend(QChart *chart): QGraphicsWidget(chart),
    d_ptr(new QLegendPrivate(chart->d_ptr->m_presenter, chart, this))
{
    setZValue(ChartPresenter::LegendZValue);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    QObject::connect(chart->d_ptr->m_dataset, SIGNAL(seriesAdded(QAbstractSeries*,Domain*)), d_ptr.data(), SLOT(handleSeriesAdded(QAbstractSeries*)));
    QObject::connect(chart->d_ptr->m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)), d_ptr.data(), SLOT(handleSeriesRemoved(QAbstractSeries*)));
//    QObject::connect(chart->d_ptr->m_dataset,SIGNAL(seriesUpdated(QAbstractSeries*)),d_ptr.data(),SLOT(handleSeriesUpdated(QAbstractSeries*)));
    setLayout(d_ptr->m_layout);
}

/*!
    Destroys the legend object. Legend is always owned by a QChart, so an application should never call this.
*/
QLegend::~QLegend()
{
}

/*!
 \internal
 */
void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!d_ptr->m_backgroundVisible)
        return;

    painter->setOpacity(opacity());
    painter->setPen(d_ptr->m_pen);
    painter->setBrush(d_ptr->m_brush);
    painter->drawRoundRect(rect(), d_ptr->roundness(rect().width()), d_ptr->roundness(rect().height()));
}


/*!
 Sets the \a brush of legend. Brush affects the background of legend.
 */
void QLegend::setBrush(const QBrush &brush)
{
    if (d_ptr->m_brush != brush) {
        d_ptr->m_brush = brush;
        update();
        emit colorChanged(brush.color());
    }
}

/*!
 Returns the brush used by legend.
 */
QBrush QLegend::brush() const
{
    return d_ptr->m_brush;
}

void QLegend::setColor(QColor color)
{
    QBrush b = d_ptr->m_brush;
    if (b.style() != Qt::SolidPattern || b.color() != color) {
        b.setStyle(Qt::SolidPattern);
        b.setColor(color);
        setBrush(b);
    }
}

QColor QLegend::color()
{
    return d_ptr->m_brush.color();
}

/*!
 Sets the \a pen of legend. Pen affects the legend borders.
 */
void QLegend::setPen(const QPen &pen)
{
    if (d_ptr->m_pen != pen) {
        d_ptr->m_pen = pen;
        update();
        emit borderColorChanged(pen.color());
    }
}

/*!
 Returns the pen used by legend
 */

QPen QLegend::pen() const
{
    return d_ptr->m_pen;
}

void QLegend::setFont(const QFont &font)
{
    if (d_ptr->m_font != font)
        d_ptr->m_font = font;

    foreach (QLegendMarker *marker, d_ptr->legendMarkers()) {
        marker->setFont(d_ptr->m_font);
        layout()->invalidate();
        emit fontChanged(font);
    }
}

QFont QLegend::font() const
{
    return d_ptr->m_font;
}

void QLegend::setBorderColor(QColor color)
{
    QPen p = d_ptr->m_pen;
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
    }
}

QColor QLegend::borderColor()
{
    return d_ptr->m_pen.color();
}

/*!
    Set brush used to draw labels to \a brush.
*/
void QLegend::setLabelBrush(const QBrush &brush)
{
    if (d_ptr->m_labelBrush != brush) {
        d_ptr->m_labelBrush = brush;
        foreach (QLegendMarker *marker, d_ptr->legendMarkers()) {
            marker->setLabelBrush(d_ptr->m_labelBrush);
            // Note: The pen of the marker rectangle could be exposed in the public QLegend API
            // instead of mapping it from label brush color
            marker->setPen(brush.color());
        }
        emit labelColorChanged(brush.color());
    }
}

/*!
    Brush used to draw labels.
*/
QBrush QLegend::labelBrush() const
{
    return d_ptr->m_labelBrush;
}

void QLegend::setLabelColor(QColor color)
{
    QBrush b = d_ptr->m_labelBrush;
    if (b.style() != Qt::SolidPattern || b.color() != color) {
        b.setStyle(Qt::SolidPattern);
        b.setColor(color);
        setLabelBrush(b);
    }
}

QColor QLegend::labelColor() const
{
    return d_ptr->m_labelBrush.color();
}


void QLegend::setAlignment(Qt::Alignment alignment)
{
    if (d_ptr->m_alignment != alignment) {
        d_ptr->m_alignment = alignment;
        layout()->invalidate();
    }
}

Qt::Alignment QLegend::alignment() const
{
    return d_ptr->m_alignment;
}

/*!
 Detaches the legend from chart. Chart won't change layout of the legend.
 */
void QLegend::detachFromChart()
{
    d_ptr->m_attachedToChart = false;
    layout()->invalidate();
    setParent(0);

}

/*!
 Attaches the legend to chart. Chart may change layout of the legend.
 */
void QLegend::attachToChart()
{
    d_ptr->m_attachedToChart = true;
    layout()->invalidate();
    setParent(d_ptr->m_chart);
}

/*!
 Returns true, if legend is attached to chart.
 */
bool QLegend::isAttachedToChart()
{
    return d_ptr->m_attachedToChart;
}

/*!
 Sets the visibility of legend background to \a visible
 */
void QLegend::setBackgroundVisible(bool visible)
{
    if (d_ptr->m_backgroundVisible != visible) {
        d_ptr->m_backgroundVisible = visible;
        update();
        emit backgroundVisibleChanged(visible);
    }
}

/*!
 Returns the visibility of legend background
 */
bool QLegend::isBackgroundVisible() const
{
    return d_ptr->m_backgroundVisible;
}


QList<QLegendMarker*> QLegend::markers() const
{
    // TODO: name of PIMPL method will change.
    return d_ptr->legendMarkers();
}

void QLegend::appendSeries(QAbstractSeries* series)
{
    d_ptr->appendSeries(series);
}

void QLegend::removeSeries(QAbstractSeries* series)
{
    d_ptr->removeSeries(series);
}

/*!
 \internal \a event see QGraphicsWidget for details
 */
void QLegend::hideEvent(QHideEvent *event)
{
    if (isAttachedToChart())
        d_ptr->m_presenter->layout()->invalidate();
    QGraphicsWidget::hideEvent(event);
}
/*!
 \internal \a event see QGraphicsWidget for details
 */
void QLegend::showEvent(QShowEvent *event)
{
    if (isAttachedToChart()) {
        d_ptr->items()->setVisible(false);
        layout()->invalidate();
    }
    QGraphicsWidget::showEvent(event);
    //layout activation will show the items
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QLegendPrivate::QLegendPrivate(ChartPresenter *presenter, QChart *chart, QLegend *q)
    : q_ptr(q),
      m_presenter(presenter),
      m_layout(new LegendLayout(q)),
      m_chart(chart),
      m_items(new QGraphicsItemGroup(q)),
      m_alignment(Qt::AlignTop),
      m_brush(QBrush()),
      m_pen(QPen()),
      m_labelBrush(QBrush()),
      m_diameter(5),
      m_attachedToChart(true),
      m_backgroundVisible(false)
{
    m_items->setHandlesChildEvents(false);
}

QLegendPrivate::~QLegendPrivate()
{

}

void QLegendPrivate::setOffset(qreal x, qreal y)
{
    m_layout->setOffset(x, y);
}

QPointF QLegendPrivate::offset() const
{
    return m_layout->offset();
}

int QLegendPrivate::roundness(qreal size)
{
    return 100 * m_diameter / int(size);
}

void QLegendPrivate::appendSeries(QAbstractSeries* series)
{
    // Only allow one instance of series
    if (m_series.contains(series)) {
        qDebug() << "series already added" << series;
        return;
    }

    QList<QLegendMarker*> newMarkers = series->d_ptr->createLegendMarkers(q_ptr);
    decorateMarkers(newMarkers);
    addMarkers(newMarkers);

    // TODO: This is the part I don't like. There should be better solution.
    // On the other hand. It is only one switch case for appending and another for removing series
    // If countChanged signal were on QAbstractSeries, there would be no need for switch at all.
    switch (series->type())
    {
    case QAbstractSeries::SeriesTypePie: {
        QPieSeries *s = qobject_cast<QPieSeries *> (series);
        QObject::connect(s, SIGNAL(countChanged()), this, SLOT(handleSeriesUpdated()));
        break;
    }
    case QAbstractSeries::SeriesTypeBar:
    case QAbstractSeries::SeriesTypeStackedBar:
    case QAbstractSeries::SeriesTypePercentBar:
    case QAbstractSeries::SeriesTypeHorizontalBar:
    case QAbstractSeries::SeriesTypeHorizontalStackedBar:
    case QAbstractSeries::SeriesTypeHorizontalPercentBar: {
        QAbstractBarSeries *s = qobject_cast<QAbstractBarSeries *> (series);
        QObject::connect(s, SIGNAL(countChanged()), this, SLOT(handleSeriesUpdated()));
        break;
    }
    case QAbstractSeries::SeriesTypeLine:
    case QAbstractSeries::SeriesTypeArea:
    case QAbstractSeries::SeriesTypeScatter:
    case QAbstractSeries::SeriesTypeSpline:
    default: {
        // No need to connect any series related signals. We have no series level
        // changes, that would generate or delete markers
    }
    }

    QObject::connect(series, SIGNAL(visibleChanged()), this, SLOT(handleSeriesVisibleChanged()));

    m_series.append(series);
    m_items->setVisible(false);
    m_layout->invalidate();
}

void QLegendPrivate::removeSeries(QAbstractSeries* series)
{
    if (m_series.contains(series)) {
        m_series.removeOne(series);
    }

    // Find out, which markers to remove
    QList<QLegendMarker *> removed;
    foreach (QLegendMarker *m, m_legendMarkers) {
        if (m->series() == series) {
            removed << m;
        }
    }
    removeMarkers(removed);

    switch (series->type())
    {
    case QAbstractSeries::SeriesTypePie: {
        QPieSeries *s = qobject_cast<QPieSeries *> (series);
        QObject::disconnect(s, SIGNAL(countChanged()), this, SLOT(handleSeriesUpdated()));
        break;
    }
    case QAbstractSeries::SeriesTypeBar:
    case QAbstractSeries::SeriesTypeStackedBar:
    case QAbstractSeries::SeriesTypePercentBar:
    case QAbstractSeries::SeriesTypeHorizontalBar:
    case QAbstractSeries::SeriesTypeHorizontalStackedBar:
    case QAbstractSeries::SeriesTypeHorizontalPercentBar: {
        QAbstractBarSeries *s = qobject_cast<QAbstractBarSeries *> (series);
        QObject::disconnect(s, SIGNAL(countChanged()), this, SLOT(handleSeriesUpdated()));
        break;
    }
    // TODO:
    case QAbstractSeries::SeriesTypeLine:
    case QAbstractSeries::SeriesTypeArea:
    case QAbstractSeries::SeriesTypeScatter:
    case QAbstractSeries::SeriesTypeSpline:
    default: {
        // No need to disconnect any series related signals
        break;
    }
    }

    QObject::disconnect(series, SIGNAL(visibleChanged()), this, SLOT(handleSeriesVisibleChanged()));

    m_layout->invalidate();
//    q_ptr->layout()->activate();
}

void QLegendPrivate::handleSeriesAdded(QAbstractSeries *series)
{
    // Moved to appendSeries
    // This slot is just to make old code work for now.
    appendSeries(series);
}

void QLegendPrivate::handleSeriesRemoved(QAbstractSeries *series)
{
    // Moved to removeSeries
    // This slot is just to make old code work for now.
    removeSeries(series);
}

void QLegendPrivate::handleSeriesVisibleChanged()
{
    QAbstractSeries *series = qobject_cast<QAbstractSeries *> (sender());
    Q_ASSERT(series);

    foreach (QLegendMarker* marker, m_legendMarkers) {
        if (marker->series() == series) {
            marker->setVisible(series->isVisible());
        }
    }
    m_layout->invalidate();
}

void QLegendPrivate::handleCountChanged()
{
    // Here we handle the changes in marker count.
    // Can happen for example when pieslice(s) have been added to or removed from pieseries.

    QAbstractSeries *series = qobject_cast<QAbstractSeries *> (sender());
    qDebug() << "QLegendPrivate::handleSeriesUpdated" << series;

    QList<QLegendMarker *> createdMarkers = series->d_ptr->createLegendMarkers(q_ptr);

    // Find out removed markers and created markers
    QList<QLegendMarker *> removedMarkers;
    foreach (QLegendMarker *oldMarker, m_legendMarkers) {
        // we have marker, which is related to sender.
        if (oldMarker->series() == series) {
            bool found = false;
            foreach(QLegendMarker *newMarker, createdMarkers) {
                // New marker considered existing if:
                // - d_ptr->relatedObject() is same for both markers.
                if (newMarker->d_ptr->relatedObject() == oldMarker->d_ptr->relatedObject()) {
                    // Delete the new marker, since we already have existing marker, that might be connected on user side.
                    found = true;
                    createdMarkers.removeOne(newMarker);
                    delete newMarker;
                }
            }
            if (!found) {
                // No related object found for marker, add to removedMarkers list
                removedMarkers << oldMarker;
            }
        }
    }

    removeMarkers(removedMarkers);
    decorateMarkers(createdMarkers);
    addMarkers(createdMarkers);

    q_ptr->layout()->invalidate();
}

void QLegendPrivate::addMarkers(QList<QLegendMarker *> markers)
{
    foreach (QLegendMarker* marker, markers) {
        m_items->addToGroup(marker->d_ptr.data()->item());
        m_legendMarkers << marker;
    }
}

void QLegendPrivate::removeMarkers(QList<QLegendMarker *> markers)
{
    foreach (QLegendMarker *marker, markers) {
        marker->d_ptr->item()->setVisible(false);
        m_items->removeFromGroup(marker->d_ptr->item());
        delete marker;
        m_legendMarkers.removeOne(marker);
    }
}

void QLegendPrivate::decorateMarkers(QList<QLegendMarker *> markers)
{
    foreach (QLegendMarker* marker, markers) {
        marker->setFont(m_font);
        marker->setLabelBrush(m_labelBrush);
    }
}


#include "moc_qlegend.cpp"
#include "moc_qlegend_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
