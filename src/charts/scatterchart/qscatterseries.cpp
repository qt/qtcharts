// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QScatterSeries>
#include <private/qscatterseries_p.h>
#include <private/scatterchartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <private/scatteranimation_p.h>
#include <private/qchart_p.h>

/*!
    \class QScatterSeries
    \inmodule QtCharts
    \brief The QScatterSeries class presents data in scatter charts.

    The scatter data is displayed as a collection of points on the chart. For
    each point, two values are specified that determine its position on the
    horizontal axis and the vertical axis.

    \image examples_scatterchart.png

    The following code snippet illustrates how to create a basic scatter chart:
    \code
    QScatterSeries* series = new QScatterSeries();
    series->append(0, 6);
    series->append(2, 4);
    ...
    chart->addSeries(series);
    \endcode

    For more information, see \l{Charts with Widgets Gallery} and
    \l {Creating Scatter Charts}.
*/
/*!
    \qmltype ScatterSeries
    \nativetype QScatterSeries
    \inqmlmodule QtCharts

    \inherits XYSeries

    \brief The ScatterSeries type presents data in scatter charts.

    The scatter data is displayed as a collection of points on the chart. For
    each point, two values are specified that determine its position on the
    horizontal axis and the vertical axis.

    \image examples_qmlchart5.png

    The following QML code shows how to create a chart with two simple scatter
    series:
    \snippet qmlchartsgallery/qml/ScatterSeries.qml 1

    For more information, see \l{Charts with QML Gallery}.
*/

/*!
    \enum QScatterSeries::MarkerShape

    This enum value describes the shape used when rendering marker items.

    \value MarkerShapeCircle
           The marker is a circle. This is the default value.
    \value MarkerShapeRectangle
           The marker is a rectangle.
    \value MarkerShapeRotatedRectangle
           The marker is a rotated rectangle.
    \value MarkerShapeTriangle
           The marker is a triangle.
    \value MarkerShapeStar
           The marker is a star.
    \value MarkerShapePentagon
           The marker is a pentagon.
*/

/*!
    \property QScatterSeries::brush
    \brief The brush used to draw the scatter series markers.

    The brush can be an image that can be created using QPainterPath,
    for example.
*/

/*!
    \qmlproperty brush ScatterSeries::brush
    The brush used to draw the scatter series markers.
*/

/*!
    \property QScatterSeries::color
    \brief The color used to fill the series markers.

    This is a convenience property for modifying the color of the brush.
    \sa QScatterSeries::brush()
*/

/*!
    \property QScatterSeries::borderColor
    \brief The color used to draw the marker borders.

    This is a convenience property for modifying the color of the pen.
    \sa QScatterSeries::pen()
*/

/*!
    \qmlproperty int ScatterSeries::count
    The number of data points in the series.
*/

/*!
    \qmlproperty color ScatterSeries::borderColor
    The color used to draw the marker borders.
*/

/*!
    \qmlproperty real ScatterSeries::borderWidth
    The width of the border line. By default, the width is 2.0.
*/

/*!
    \property QScatterSeries::markerShape
    \brief The shape of the marker used to render the points in the series.

    The default shape is MarkerShapeCircle.

    \sa MarkerShape
*/
/*!
    \qmlproperty enumeration ScatterSeries::markerShape

    The shape used when rendering marker items:

    \value ScatterSeries.MarkerShapeCircle
           The marker is a circle. This is the default value.
    \value ScatterSeries.MarkerShapeRectangle
           The marker is a rectangle.
*/

/*!
    \property QScatterSeries::markerSize
    \brief The size of the marker used to render the points in the series.

    \sa QXYSeries::setMarkerSize
*/
/*!
    \qmlproperty real ScatterSeries::markerSize
    The size of the marker used to render the points in the series.
*/

/*!
    \qmlproperty string ScatterSeries::brushFilename
    The name of the file used as a brush for the series.
*/

/*!
    \fn void QScatterSeries::colorChanged(QColor color)
    This signal is emitted when the fill (brush) color changes to \a color.
*/

/*!
    \fn void QScatterSeries::borderColorChanged(QColor color)
    This signal is emitted when the line (pen) color changes to \a color.
*/

/*!
    \fn void QScatterSeries::markerShapeChanged(MarkerShape shape)
    This signal is emitted when the marker shape changes to \a shape.
*/

/*!
    \fn void QScatterSeries::markerSizeChanged(qreal size)
    This signal is emitted when the marker size changes to \a size.
*/

QT_BEGIN_NAMESPACE

/*!
    Constructs a series object that is a child of \a parent.
*/
QScatterSeries::QScatterSeries(QObject *parent)
    : QXYSeries(*new QScatterSeriesPrivate(this), parent)
{
    setPointsVisible(true);

    // Emit QScatterSeries' markerSizeChanged signal as it's not the same as
    // QXYSeries' markerSizeChanged
    connect(this, &QXYSeries::markerSizeChanged, this, &QScatterSeries::markerSizeChanged);
}

/*!
    Deletes the scatter series.

    \note Adding the series to QChart transfers the ownership to the chart.
*/
QScatterSeries::~QScatterSeries()
{
    Q_D(QScatterSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    \reimp
*/
QAbstractSeries::SeriesType QScatterSeries::type() const
{
    return QAbstractSeries::SeriesTypeScatter;
}

/*!
    \reimp
*/
void QScatterSeries::setPen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_pen != pen) {
        bool emitColorChanged = d->m_pen.color() != pen.color();
        d->m_pen = pen;
        emit d->seriesUpdated();
        if (emitColorChanged)
            emit borderColorChanged(pen.color());
    }
}

/*!
    \reimp
*/
void QScatterSeries::setBrush(const QBrush &brush)
{
    Q_D(QScatterSeries);
    if (d->m_brush != brush) {
        bool emitColorChanged = d->m_brush.color() != brush.color();
        d->m_brush = brush;
        emit d->seriesUpdated();
        if (emitColorChanged)
            emit colorChanged(brush.color());
    }
}

QBrush QScatterSeries::brush() const
{
    Q_D(const QScatterSeries);
    if (d->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d->m_brush;
}

void QScatterSeries::setColor(const QColor &color)
{
    QBrush b = brush();
    if (b == QChartPrivate::defaultBrush())
        b = QBrush();
    if (b == QBrush())
        b.setStyle(Qt::SolidPattern);
    b.setColor(color);
    setBrush(b);
}

QColor QScatterSeries::color() const
{
    return brush().color();
}

void QScatterSeries::setBorderColor(const QColor &color)
{
    QPen p = pen();
    if (p == QChartPrivate::defaultPen())
        p = QPen();
    p.setColor(color);
    setPen(p);
}

QColor QScatterSeries::borderColor() const
{
    return pen().color();
}

QScatterSeries::MarkerShape QScatterSeries::markerShape() const
{
    Q_D(const QScatterSeries);
    return d->m_shape;
}

void QScatterSeries::setMarkerShape(MarkerShape shape)
{
    Q_D(QScatterSeries);
    if (d->m_shape != shape) {
        d->m_shape = shape;
        emit d->seriesUpdated();
        emit markerShapeChanged(shape);
    }
}

qreal QScatterSeries::markerSize() const
{
    // markerSize has moved to QXYSeries, but this method needs to remain for API compatibility.
    return QXYSeries::markerSize();
}
void QScatterSeries::setMarkerSize(qreal size)
{
    // markerSize has moved to QXYSeries, but this method needs to remain for API compatibility.
    QXYSeries::setMarkerSize(size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QScatterSeriesPrivate::QScatterSeriesPrivate(QScatterSeries *q)
    : QXYSeriesPrivate(q),
      m_shape(QScatterSeries::MarkerShapeCircle)
{
}

void QScatterSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QScatterSeries);
    ScatterChartItem *scatter = new ScatterChartItem(q,parent);
    m_item.reset(scatter);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

void QScatterSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    Q_Q(QScatterSeries);
    const QList<QColor> colors = theme->seriesColors();
    const QList<QGradient> gradients = theme->seriesGradients();

    if (forced || QChartPrivate::defaultPen() == m_pen) {
        QPen pen;
        pen.setColor(ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 0.0));
        pen.setWidthF(2);
        q->setPen(pen);
    }

    if (forced || QChartPrivate::defaultBrush() == m_brush) {
        QBrush brush(colors.at(index % colors.size()));
        q->setBrush(brush);
    }

    if (forced || QChartPrivate::defaultPen().color() == m_pointLabelsColor) {
        QColor color = theme->labelBrush().color();
        q->setPointLabelsColor(color);
    }
}

void QScatterSeriesPrivate::initializeAnimations(QChart::AnimationOptions options, int duration,
                                                 QEasingCurve &curve)
{
    ScatterChartItem *item = static_cast<ScatterChartItem *>(m_item.get());
    Q_ASSERT(item);

    if (item->animation())
        item->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        item->setAnimation(new ScatterAnimation(item, duration, curve));
    else
        item->setAnimation(0);

    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);
}

QT_END_NAMESPACE

#include "moc_qscatterseries.cpp"
