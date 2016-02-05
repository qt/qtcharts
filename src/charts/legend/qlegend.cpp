/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QLegend>
#include <private/qlegend_p.h>
#include <QtCharts/QAbstractSeries>
#include <private/qabstractseries_p.h>
#include <private/qchart_p.h>
#include <private/legendlayout_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCharts/QLegendMarker>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <private/chartdataset_p.h>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsItemGroup>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QLegend
    \inmodule Qt Charts
    \inherits QGraphicsWidget
    \brief Legend object.

    QLegend is a graphical object for displaying the legend of the chart. Legend state is updated by QChart, when
    series have been changed. By default, legend is drawn by QChart, but user can set a new parent to legend and
    handle the drawing manually.
    User isn't supposed to create or delete legend objects, but can reference it via QChart class.

    \image examples_percentbarchart_legend.png

    \sa QChart
*/
/*!
    \qmltype Legend
    \instantiates QLegend
    \inqmlmodule QtCharts

    \brief Legend is part of Qt Chart QML API.

    Legend is a graphical object, which displays legend of the chart. Legend state is updated by
    ChartView, when series have been changed. Legend is used via ChartView class. For example:
    \code
        ChartView {
            legend.visible: true
            legend.alignment: Qt.AlignBottom
            // Add a few series...
        }
    \endcode

    \image examples_percentbarchart_legend.png

    Please note that there is no QML API available for modifying legend markers, unlike in the Qt
    API of Charts. The use case of modifying markers can be implemented for example by creating your
    own custom legend. For an example on how to do this,
    see \l {qmlcustomlegend}{Qml Custom Example} application.
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
    \qmlproperty bool Legend::visible
    \brief Whether the legend is visible or not.

    By default, this property is \c true.
    \sa QGraphicsObject::visible
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
    The font of markers used by legend.
*/
/*!
    \qmlproperty Font Legend::font
    The font of markers used by legend.
*/

/*!
    \property QLegend::labelColor
    The color of brush used to draw labels.
*/
/*!
    \qmlproperty color Legend::labelColor
    The color of brush used to draw labels.
*/

/*!
    \property QLegend::reverseMarkers
    Whether reverse order is used for the markers in legend or not. False by default.
*/
/*!
    \qmlproperty bool Legend::reverseMarkers
    Whether reverse order is used for the markers in legend or not. False by default.
*/

/*!
    \property QLegend::showToolTips
    Whether tooltips are shown when the text is truncated. This is false by default.

    This will not have any effect when used in QML.
*/

/*!
    \qmlproperty bool Legend::showToolTips
    Whether tooltips are shown when the text is truncated. This is false by default.
    This currently has no effect as there is no support for tooltips in QML.
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
    \fn void QLegend::reverseMarkersChanged(bool)
    The use of reverse order for the markers in legend is changed to \a reverseMarkers.
*/

/*!
    \fn void QLegend::showToolTipsChanged(bool showToolTips)
    This signal is emitted when the visibility of tooltips is changed to \a showToolTips.
*/

QLegend::QLegend(QChart *chart): QGraphicsWidget(chart),
    d_ptr(new QLegendPrivate(chart->d_ptr->m_presenter, chart, this))
{
    setZValue(ChartPresenter::LegendZValue);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    QObject::connect(chart->d_ptr->m_dataset, SIGNAL(seriesAdded(QAbstractSeries*)), d_ptr.data(), SLOT(handleSeriesAdded(QAbstractSeries*)));
    QObject::connect(chart->d_ptr->m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)), d_ptr.data(), SLOT(handleSeriesRemoved(QAbstractSeries*)));
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
    if (d_ptr->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d_ptr->m_brush;
}

void QLegend::setColor(QColor color)
{
    QBrush b = brush();
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
 Returns the pen used by legend.
 */

QPen QLegend::pen() const
{
    if (d_ptr->m_pen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d_ptr->m_pen;
}

void QLegend::setFont(const QFont &font)
{
    if (d_ptr->m_font != font) {
        // Hide items to avoid flickering
        d_ptr->items()->setVisible(false);
        d_ptr->m_font = font;
        foreach (QLegendMarker *marker, d_ptr->markers()) {
            marker->setFont(d_ptr->m_font);
        }
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
    QPen p = pen();
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
        foreach (QLegendMarker *marker, d_ptr->markers()) {
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
    if (d_ptr->m_labelBrush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d_ptr->m_labelBrush;
}

void QLegend::setLabelColor(QColor color)
{
    QBrush b = labelBrush();
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
//    layout()->invalidate();
    d_ptr->m_chart->layout()->invalidate();
    setParent(0);

}

/*!
 Attaches the legend to chart. Chart may change layout of the legend.
 */
void QLegend::attachToChart()
{
    d_ptr->m_attachedToChart = true;
//    layout()->invalidate();
    d_ptr->m_chart->layout()->invalidate();
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

/*!
  Returns the list of markers in legend. The list can be filtered with \a series parameter.
  If \a series is given, only markers related to that series are returned.
*/
QList<QLegendMarker*> QLegend::markers(QAbstractSeries *series) const
{
    return d_ptr->markers(series);
}

bool QLegend::reverseMarkers()
{
    return d_ptr->m_reverseMarkers;
}

void QLegend::setReverseMarkers(bool reverseMarkers)
{
    if (d_ptr->m_reverseMarkers != reverseMarkers) {
        d_ptr->m_reverseMarkers = reverseMarkers;
        layout()->invalidate();
        emit reverseMarkersChanged(reverseMarkers);
    }
}

/*!
    Returns whether the tooltips are shown or not for the legend labels
    when they are elided.
*/

bool QLegend::showToolTips() const
{
    return d_ptr->m_showToolTips;
}

/*!
    When \a show is true, the legend labels will show a tooltip when
    the mouse hovers over them if the label itself is shown elided.
    This is false by default.
*/

void QLegend::setShowToolTips(bool show)
{
    if (d_ptr->m_showToolTips != show) {
        d_ptr->m_showToolTips = show;
        d_ptr->updateToolTips();
        emit showToolTipsChanged(show);
    }
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
    if (isAttachedToChart())
        layout()->invalidate();
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
      m_brush(QChartPrivate::defaultBrush()),
      m_pen(QChartPrivate::defaultPen()),
      m_labelBrush(QChartPrivate::defaultBrush()),
      m_diameter(5),
      m_attachedToChart(true),
      m_backgroundVisible(false),
      m_reverseMarkers(false),
      m_showToolTips(false)
{
    m_items->setHandlesChildEvents(false);
}

QLegendPrivate::~QLegendPrivate()
{

}

void QLegendPrivate::setOffset(const QPointF &offset)
{
    m_layout->setOffset(offset.x(), offset.y());
}

QPointF QLegendPrivate::offset() const
{
    return m_layout->offset();
}

int QLegendPrivate::roundness(qreal size)
{
    return 100 * m_diameter / int(size);
}

QList<QLegendMarker*> QLegendPrivate::markers(QAbstractSeries *series)
{
    // Return all markers
    if (!series) {
        return m_markers;
    }

    // Create filtered list
    QList<QLegendMarker *> markers;
    foreach (QLegendMarker *marker, m_markers) {
        if (marker->series() == series) {
            markers.append(marker);
        }
    }
    return markers;
}

void QLegendPrivate::handleSeriesAdded(QAbstractSeries *series)
{
    if (m_series.contains(series)) {
        return;
    }

    QList<QLegendMarker*> newMarkers = series->d_ptr->createLegendMarkers(q_ptr);
    decorateMarkers(newMarkers);
    addMarkers(newMarkers);

    QObject::connect(series->d_ptr.data(), SIGNAL(countChanged()), this, SLOT(handleCountChanged()));
    QObject::connect(series, SIGNAL(visibleChanged()), this, SLOT(handleSeriesVisibleChanged()));

    m_series.append(series);
    m_items->setVisible(false);
    m_layout->invalidate();
}

void QLegendPrivate::handleSeriesRemoved(QAbstractSeries *series)
{
    if (m_series.contains(series)) {
        m_series.removeOne(series);
    }

    // Find out, which markers to remove
    QList<QLegendMarker *> removed;
    foreach (QLegendMarker *m, m_markers) {
        if (m->series() == series) {
            removed << m;
        }
    }
    removeMarkers(removed);

    QObject::disconnect(series->d_ptr.data(), SIGNAL(countChanged()), this, SLOT(handleCountChanged()));
    QObject::disconnect(series, SIGNAL(visibleChanged()), this, SLOT(handleSeriesVisibleChanged()));

    m_layout->invalidate();
}

void QLegendPrivate::handleSeriesVisibleChanged()
{
    QAbstractSeries *series = qobject_cast<QAbstractSeries *> (sender());
    Q_ASSERT(series);

    foreach (QLegendMarker *marker, m_markers) {
        if (marker->series() == series) {
            marker->setVisible(series->isVisible());
        }
    }

    if (m_chart->isVisible())
        m_layout->invalidate();
}

void QLegendPrivate::handleCountChanged()
{
    // Here we handle the changes in marker count.
    // Can happen for example when pieslice(s) have been added to or removed from pieseries.

    QAbstractSeriesPrivate *series = qobject_cast<QAbstractSeriesPrivate *> (sender());
    QList<QLegendMarker *> createdMarkers = series->createLegendMarkers(q_ptr);

    // Find out removed markers and created markers
    QList<QLegendMarker *> removedMarkers;
    foreach (QLegendMarker *oldMarker, m_markers) {
        // we have marker, which is related to sender.
        if (oldMarker->series() == series->q_ptr) {
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
    foreach (QLegendMarker *marker, markers) {
        m_items->addToGroup(marker->d_ptr.data()->item());
        m_markers << marker;
        m_markerHash.insert(marker->d_ptr->item(), marker);
    }
}

void QLegendPrivate::removeMarkers(QList<QLegendMarker *> markers)
{
    foreach (QLegendMarker *marker, markers) {
        marker->d_ptr->item()->setVisible(false);
        m_items->removeFromGroup(marker->d_ptr->item());
        m_markers.removeOne(marker);
        m_markerHash.remove(marker->d_ptr->item());
        delete marker;
    }
}

void QLegendPrivate::decorateMarkers(QList<QLegendMarker *> markers)
{
    foreach (QLegendMarker *marker, markers) {
        marker->setFont(m_font);
        marker->setLabelBrush(m_labelBrush);
    }
}

void QLegendPrivate::updateToolTips()
{
    foreach (QLegendMarker *m, m_markers) {
        if (m->d_ptr->m_item->displayedLabel() != m->label())
            m->d_ptr->m_item->setToolTip(m->label());
        else
            m->d_ptr->m_item->setToolTip(QString());
    }
}
#include "moc_qlegend.cpp"
#include "moc_qlegend_p.cpp"

QT_CHARTS_END_NAMESPACE
