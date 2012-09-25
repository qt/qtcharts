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

#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "scatterchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"

/*!
    \class QScatterSeries
    \brief The QScatterSeries class is used for making scatter charts.

    \mainclass

    The scatter data is displayed as a collection of points on the chart. Each point determines the position on the horizontal axis
    and the vertical axis.

    \image examples_scatterchart.png

    Creating basic scatter chart is simple:
    \code
    QScatterSeries* series = new QScatterSeries();
    series->append(0, 6);
    series->append(2, 4);
    ...
    chart->addSeries(series);
    \endcode
*/
/*!
    \qmlclass ScatterSeries QScatterSeries
    \inherits XYSeries

    The following QML shows how to create a chart with two simple scatter series:
    \snippet ../demos/qmlchart/qml/qmlchart/View5.qml 1

    \beginfloatleft
    \image demos_qmlchart5.png
    \endfloat
    \clearfloat
*/

/*!
    \enum QScatterSeries::MarkerShape

    This enum describes the shape used when rendering marker items.

    \value MarkerShapeCircle
    \value MarkerShapeRectangle
*/

/*!
    \property QScatterSeries::color
    Fill (brush) color of the series. This is a convenience property for modifying the color of brush.
    \sa QScatterSeries::brush()
*/

/*!
    \property QScatterSeries::borderColor
    Line (pen) color of the series. This is a convenience property for modifying the color of pen.
    \sa QScatterSeries::pen()
*/

/*!
    \qmlproperty real ScatterSeries::borderWidth
    The width of the border line. By default the width is 2.0.
*/

/*!
    \property QScatterSeries::markerShape
    Defines the shape of the marker used to draw the points in the series. The default shape is MarkerShapeCircle.
*/
/*!
    \qmlproperty MarkerShape ScatterSeries::markerShape
    Defines the shape of the marker used to draw the points in the series. One of ScatterSeries
    ScatterSeries.MarkerShapeCircle or ScatterSeries.MarkerShapeRectangle.
    The default shape is ScatterSeries.MarkerShapeCircle.
*/

/*!
    \property QScatterSeries::markerSize
    Defines the size of the marker used to draw the points in the series. The default size is 15.0.
*/
/*!
    \qmlproperty real ScatterSeries::markerSize
    Defines the size of the marker used to draw the points in the series. The default size is 15.0.
*/

/*!
    \fn void QScatterSeries::colorChanged(QColor color)
    Signal is emitted when the fill (brush) color has changed to \a color.
*/

/*!
    \fn void QScatterSeries::borderColorChanged(QColor color)
    Signal is emitted when the line (pen) color has changed to \a color.
*/
/*!
    \qmlsignal ScatterSeries::borderColorChanged(color color)
    Signal is emitted when the line (pen) color has changed to \a color.
*/

/*!
    \fn QChartSeriesType QScatterSeries::type() const
    Returns QChartSeries::SeriesTypeScatter.
    \sa QAbstractSeries, SeriesType
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs a series object which is a child of \a parent.
*/
QScatterSeries::QScatterSeries(QObject *parent)
    : QXYSeries(*new QScatterSeriesPrivate(this), parent)
{
}

/*!
    Destroys the object. Note that adding series to QChart transfers the ownership to the chart.
*/
QScatterSeries::~QScatterSeries()
{
    Q_D(QScatterSeries);
    if (d->m_dataset)
        d->m_dataset->removeSeries(this);
}

QAbstractSeries::SeriesType QScatterSeries::type() const
{
    return QAbstractSeries::SeriesTypeScatter;
}

/*!
    Sets \a pen used for drawing points' border on the chart. If the pen is not defined, the
    pen from chart theme is used.
    \sa QChart::setTheme()
*/
void QScatterSeries::setPen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_pen != pen) {
        bool emitColorChanged = d->m_pen.color() != pen.color();
        d->m_pen = pen;
        emit d->updated();
        if (emitColorChanged)
            emit borderColorChanged(pen.color());
    }
}

/*!
    Sets \a brush used for drawing points on the chart. If the brush is not defined, brush
    from chart theme setting is used.
    \sa QChart::setTheme()
*/
void QScatterSeries::setBrush(const QBrush &brush)
{
    Q_D(QScatterSeries);
    if (d->m_brush != brush) {
        bool emitColorChanged = d->m_brush.color() != brush.color();
        d->m_brush = brush;
        emit d->updated();
        if (emitColorChanged)
            emit colorChanged(brush.color());
    }
}

void QScatterSeries::setColor(const QColor &color)
{
    QBrush b = brush();
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
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
    }
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
        emit d->updated();
    }
}

qreal QScatterSeries::markerSize() const
{
    Q_D(const QScatterSeries);
    return d->m_size;
}

void QScatterSeries::setMarkerSize(qreal size)
{
    Q_D(QScatterSeries);

    if (!qFuzzyIsNull(d->m_size - size)) {
        d->m_size = size;
        emit d->updated();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QScatterSeriesPrivate::QScatterSeriesPrivate(QScatterSeries *q)
    : QXYSeriesPrivate(q),
      m_shape(QScatterSeries::MarkerShapeCircle),
      m_size(15.0)
{
}

ChartElement *QScatterSeriesPrivate::createGraphics(ChartPresenter *presenter)
{
    Q_Q(QScatterSeries);
    ScatterChartItem *scatter = new ScatterChartItem(q, presenter);
    if (presenter->animationOptions().testFlag(QChart::SeriesAnimations))
        scatter->setAnimation(new XYAnimation(scatter));
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return scatter;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
