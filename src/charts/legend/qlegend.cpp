// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
#include <private/legendmoveresizehandler_p.h>
#include <private/chartdataset_p.h>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsItemGroup>

QT_BEGIN_NAMESPACE

/*!
    \class QLegend
    \inmodule QtCharts
    \inherits QGraphicsWidget
    \brief The QLegend class displays the legend of a chart.

    A legend is a graphical object that displays the legend of a chart. The legend state is updated
    by QChart when series change. By default, the legend is attached to the chart, but it can be
    detached to make it independent of chart layout. Legend objects cannot be created or deleted,
    but they can be referenced via the QChart class.

    \image examples_percentbarchart_legend.png

    \sa QChart
*/
/*!
    \qmltype Legend
    \instantiates QLegend
    \inqmlmodule QtCharts

    \brief Displays the legend of a chart.

    A legend is a graphical object that displays the legend of a chart. The legend state is updated
    by the ChartView type when series change. The \l Legend type properties can be attached to the
    ChartView type. For example:
    \code
        ChartView {
            legend.visible: true
            legend.alignment: Qt.AlignBottom
            // Add a few series...
        }
    \endcode

    \image examples_percentbarchart_legend.png

    \note There is no QML API available for modifying legend markers. Markers
    can be modified by creating a custom legend. For more information, see
    \l {Using Legend Markers}.
*/

/*!
    \property QLegend::alignment
    \brief How the legend is aligned with the chart.

    Can be Qt::AlignTop, Qt::AlignBottom, Qt::AlignLeft, Qt::AlignRight. If you set more than one
    flag, the result is undefined.
*/
/*!
    \qmlproperty alignment Legend::alignment
    Defines how the legend is aligned with the chart. Can be \l{Qt::AlignLeft}{Qt.AlignLeft},
    \l{Qt::AlignRight}{Qt.AlignRight}, \l{Qt::AlignBottom}{Qt.AlignBottom}, or
    \l{Qt::AlignTop}{Qt.AlignTop}. If you set more than one flag, the result is undefined.
*/

/*!
    \property QLegend::backgroundVisible
    \brief Whether the legend background is visible.
*/
/*!
    \qmlproperty bool Legend::backgroundVisible
    Whether the legend background is visible.
*/

/*!
    \qmlproperty bool Legend::visible
    Whether the legend is visible.

    By default, this property is \c true.
    \sa QGraphicsObject::visible
*/

/*!
    \property QLegend::color
    \brief The background (brush) color of the legend.

    If you change the color of the legend, the style of the legend brush is set to
    Qt::SolidPattern.
*/
/*!
    \qmlproperty color Legend::color
    The background (brush) color of the legend.
*/

/*!
    \property QLegend::borderColor
    \brief The line color of the legend.
*/
/*!
    \qmlproperty color Legend::borderColor
    The line color of the legend.
*/

/*!
    \property QLegend::font
    \brief The font of the markers used by the legend.
*/
/*!
    \qmlproperty Font Legend::font
    The font of the markers used by the legend.
*/

/*!
    \property QLegend::labelColor
    \brief The color of the brush used to draw labels.
*/
/*!
    \qmlproperty color Legend::labelColor
    The color of the brush used to draw labels.
*/

/*!
    \property QLegend::reverseMarkers
    \brief Whether reverse order is used for the markers in the legend.

    This property is \c false by default.
*/
/*!
    \qmlproperty bool Legend::reverseMarkers
    Whether reverse order is used for the markers in the legend. This property
    is \c false by default.
*/

/*!
    \property QLegend::showToolTips
    \brief Whether tooltips are shown when the text is truncated.

    This property is \c false by default.
*/

/*!
    \enum QLegend::MarkerShape

    This enum describes the shape used when rendering legend marker items.

    \value MarkerShapeDefault Default shape determined by QLegend is used for the marker.
           This value is supported only for individual QLegendMarker items.
    \value MarkerShapeRectangle Rectangular markers are used.
           Marker size is determined by font size.
    \value MarkerShapeCircle Circular markers are used.
           Marker size is determined by font size.
    \value MarkerShapeRotatedRectangle Rotated rectangle shaped markers are used.
           Marker size is determined by font size.
    \value MarkerShapeTriangle Triangular markers are used.
           Marker size is determined by font size.
    \value MarkerShapeStar Star shaped markers are used.
           Marker size is determined by font size.
    \value MarkerShapePentagon Pentagon shaped markers are used.
           Marker size is determined by font size.
    \value MarkerShapeFromSeries The marker shape is determined by the series.
           In case of a scatter series, the legend marker looks like a scatter dot and is the same
           size as the dot. In case of a line or spline series, the legend marker looks like a
           small segment of the line. For other series types, rectangular markers are shown.
           If a \c lightMarker is specified for a series, the \c lightMarker will be shown and
           its size will be determined by the series marker size.

    \sa markerShape
*/

/*!
    \qmlproperty enumeration Legend::markerShape
    \since 5.9

    The default shape of the legend markers.
    The default value is \c{MarkerShapeRectangle}.

    \value Legend.MarkerShapeRectangle Legend markers are rectangular
    \value Legend.MarkerShapeCircle Legend markers are circular
    \value MarkerShapeRotatedRectangle Legend markers are rotated rectangle shaped.
    \value MarkerShapeTriangle Legend markers are triangular.
    \value MarkerShapeStar Legend markers are star shaped.
    \value MarkerShapePentagon Legend markers are pentagon shaped.
    \value Legend.MarkerShapeFromSeries Legend marker shape is determined by the series

    \sa QLegend::MarkerShape
*/

/*!
    \property QLegend::markerShape
    \since 5.9

    The default shape of the legend markers.
    The default value is \c{MarkerShapeRectangle}.
*/

/*!
    \qmlproperty bool Legend::showToolTips
    Whether tooltips are shown when the text is truncated. This property is \c false by default.
    This property currently has no effect as there is no support for tooltips in QML.
*/

/*!
    \fn void QLegend::attachedToChartChanged(bool attached)
    This signal is emitted when the legend is \a attached to or detached from the chart.
    \since 6.2
*/

/*!
    \fn void QLegend::backgroundVisibleChanged(bool)
    This signal is emitted when the visibility of the legend background changes to \a visible.
*/

/*!
    \fn void QLegend::colorChanged(QColor)
    This signal is emitted when the color of the legend background changes to \a color.
*/

/*!
    \fn void QLegend::borderColorChanged(QColor)
    This signal is emitted when the border color of the legend background changes to \a color.
*/

/*!
    \fn void QLegend::fontChanged(QFont)
    This signal is emitted when the font of the markers of the legend changes to \a font.
*/

/*!
    \fn void QLegend::labelColorChanged(QColor color)
    This signal is emitted when the color of the brush used to draw the legend
    labels changes to \a color.
*/

/*!
    \fn void QLegend::reverseMarkersChanged(bool)
    This signal is emitted when the use of reverse order for the markers in the
    legend is changed to \a reverseMarkers.
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
    Destroys the legend object. The legend is always owned by a QChart, so an application
    should never call this function.
*/
QLegend::~QLegend()
{
}

/*!
 \internal
 */
void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!d_ptr->m_backgroundVisible)
        return;

    painter->setOpacity(opacity());
    painter->setPen(d_ptr->m_pen);
    painter->setBrush(d_ptr->m_brush);
    painter->drawRoundedRect(rect(), d_ptr->roundness(rect().width()),
                             d_ptr->roundness(rect().height()), Qt::RelativeSize);
}


/*!
    Sets the \a brush that is used to draw the background of the legend.
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
    Returns the brush used by the legend.
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
    Sets the \a pen that is used to draw the legend borders.
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
    Returns the pen used by the legend.
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
    Sets the brush used to draw the legend labels to \a brush.
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
    Returns the brush used to draw labels.
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
    Detaches the legend from the chart. The chart will no longer adjust the layout of the legend.
 */
void QLegend::detachFromChart()
{
    bool changed = d_ptr->m_attachedToChart == true;
    d_ptr->m_attachedToChart = false;
    d_ptr->m_chart->layout()->invalidate();
    setParent(0);

    if (changed)
        emit attachedToChartChanged(false);
}

/*!
    Attaches the legend to a chart. The chart may adjust the layout of the legend.
 */
void QLegend::attachToChart()
{
    bool changed = d_ptr->m_attachedToChart == false;
    d_ptr->m_attachedToChart = true;
    d_ptr->m_chart->layout()->invalidate();
    setParent(d_ptr->m_chart);

    if (changed)
        emit attachedToChartChanged(true);
}

/*!
    Returns \c true, if the legend is attached to a chart.
 */
bool QLegend::isAttachedToChart()
{
    return d_ptr->m_attachedToChart;
}

/*!
    Sets the visibility of the legend background to \a visible.
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
    Returns the visibility of the legend background.
 */
bool QLegend::isBackgroundVisible() const
{
    return d_ptr->m_backgroundVisible;
}

/*!
    Returns the list of markers in the legend. The list can be filtered by specifying
    the \a series for which the markers are returned.
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
    Returns whether the tooltips are shown for the legend labels
    when they are elided.
*/

bool QLegend::showToolTips() const
{
    return d_ptr->m_showToolTips;
}

/*!
    When \a show is \c true, the legend labels will show a tooltip when
    the mouse hovers over them if the label itself is shown elided.
    This is \c false by default.
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
    Returns whether the legend can be dragged or resized using a mouse when it is detached.

    \sa QLegend::setInteractive()
    \since 6.2
*/

bool QLegend::isInteractive() const
{
    return d_ptr->m_interactive;
}

/*!
    When \a interactive is \c true and the legend is detached, the legend is able to be moved and
    resized with a mouse in a similar way to a window.

    The legend will automatically attach to an edge of the chart by dragging it off of that edge.
    Double clicking an attached legend will detach it.
    This is \c false by default.

    \sa QLegend::isInteractive()
    \since 6.2
*/

void QLegend::setInteractive(bool interactive)
{
    if (d_ptr->m_interactive != interactive) {
        d_ptr->m_interactive = interactive;
        update();
        emit interactiveChanged(interactive);
    }
}

QLegend::MarkerShape QLegend::markerShape() const
{
    return d_ptr->m_markerShape;
}

void QLegend::setMarkerShape(QLegend::MarkerShape shape)
{
    QLegend::MarkerShape newShape = shape;
    if (newShape == MarkerShapeDefault)
        newShape = MarkerShapeRectangle;
    if (d_ptr->m_markerShape != newShape) {
        d_ptr->m_markerShape = newShape;
        layout()->invalidate();
        emit markerShapeChanged(newShape);
    }
}

/*!
    \internal
    \a event, see QGraphicsWidget for details.
 */
void QLegend::hideEvent(QHideEvent *event)
{
    if (isAttachedToChart())
        d_ptr->m_presenter->layout()->invalidate();
    QGraphicsWidget::hideEvent(event);
}
/*!
    \internal
    \a event, see QGraphicsWidget for details.
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
      m_resizer(new LegendMoveResizeHandler(q)),
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
      m_showToolTips(false),
      m_interactive(false),
      m_markerShape(QLegend::MarkerShapeRectangle)
{
    m_items->setHandlesChildEvents(false);
}

QLegendPrivate::~QLegendPrivate()
{
    delete m_resizer;
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

qreal QLegendPrivate::maxMarkerWidth() const
{
    qreal maxWidth = 0.0;
    for (int i = 0; i < m_markers.size(); i++) {
        LegendMarkerItem *item = m_markers.at(i)->d_ptr->item();
        if (item)
            maxWidth = qMax(item->markerRect().width(), maxWidth);
    }
    return maxWidth;
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

QObject *QLegendPrivate::relatedObject(const QLegendMarker *l)
{
    return l->d_ptr->relatedObject();
}

// Find equivalent QLegendMarker by checking for relatedObject()
static int indexOfEquivalent(const QLegendMarker *needle,
                             const QList<QLegendMarker *> &hayStack)
{
    const QObject *needleObject = QLegendPrivate::relatedObject(needle);
    for (int i = 0, size = hayStack.size(); i < size; ++i) {
        if (QLegendPrivate::relatedObject(hayStack.at(i)) == needleObject)
            return i;
    }
    return -1;
}

// Find QLegendMarker for series
static int indexOfSeries(const QAbstractSeries *series,
                         const QList<QLegendMarker *> &hayStack)
{
    for (int i = 0, size = hayStack.size(); i < size; ++i) {
        if (hayStack.at(i)->series() == series)
            return i;
    }
    return -1;
}

void QLegendPrivate::handleCountChanged()
{
    // Here we handle the changes in marker count.
    // Can happen for example when pieslice(s) have been added to or removed from pieseries.

    QAbstractSeriesPrivate *seriesP = qobject_cast<QAbstractSeriesPrivate *>(sender());
    QAbstractSeries *series = seriesP->q_ptr;
    QList<QLegendMarker *> createdMarkers = seriesP->createLegendMarkers(q_ptr);
    QList<bool> isNew(createdMarkers.size(), true);

    const int pos = indexOfSeries(series, m_markers);
    // Remove markers of the series from m_markers and check against the newly
    // created ones.
    if (pos != -1) {
        while (pos < m_markers.size() && m_markers.at(pos)->series() == series) {
            QLegendMarker *oldMarker = m_markers.takeAt(pos);
            const int newIndex = indexOfEquivalent(oldMarker, createdMarkers);
            if (newIndex == -1) {
                removeMarkerHelper(oldMarker); // no longer exists
            } else {
                 // Replace newly created marker by its equivalent
                delete createdMarkers[newIndex];
                createdMarkers[newIndex] = oldMarker;
                isNew[newIndex] = false;
            }
        }
    }

    for (int i = 0, size = createdMarkers.size(); i < size; ++i) {
        if (isNew.at(i)) {
            insertMarkerHelper(createdMarkers.at(i));
            decorateMarker(createdMarkers.at(i));
        }
    }

    // Re-insert createdMarkers into m_markers in correct order.
    if (pos == -1 || pos == m_markers.size()) {
        m_markers.append(createdMarkers);
    } else {
        for (int c = createdMarkers.size() - 1; c >= 0; --c)
            m_markers.insert(pos, createdMarkers.at(c));
    }

    q_ptr->layout()->invalidate();
}

// Helper function for marker insertion except m_markers handling
void QLegendPrivate::insertMarkerHelper(QLegendMarker *marker)
{
    LegendMarkerItem *item = marker->d_ptr->item();
    m_items->addToGroup(item);
    m_markerHash.insert(item, marker);
}

void QLegendPrivate::addMarkers(const QList<QLegendMarker *> &markers)
{
    for (auto *marker : markers) {
        insertMarkerHelper(marker);
        m_markers << marker;
    }
}

// Helper function for marker removal except m_markers handling
void QLegendPrivate::removeMarkerHelper(QLegendMarker *marker)
{
    LegendMarkerItem *item = marker->d_ptr->item();
    item->setVisible(false);
    m_items->removeFromGroup(item);
    m_markerHash.remove(item);
    delete marker;
}

void QLegendPrivate::removeMarkers(const QList<QLegendMarker *> &markers)
{
    for (auto *marker : markers) {
        m_markers.removeOne(marker);
        removeMarkerHelper(marker);
    }
}

void QLegendPrivate::decorateMarker(QLegendMarker *marker)
{
    marker->setFont(m_font);
    marker->setLabelBrush(m_labelBrush);
}

void QLegendPrivate::decorateMarkers(const QList<QLegendMarker *> &markers)
{
    for (auto *marker : markers)
        decorateMarker(marker);
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

QT_END_NAMESPACE

#include "moc_qlegend.cpp"
#include "moc_qlegend_p.cpp"
