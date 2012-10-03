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

#include "qareaseries.h"
#include "qareaseries_p.h"
#include "qlineseries.h"
#include "areachartitem_p.h"
#include "domain_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "qvalueaxis.h"
#include "qarealegendmarker.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAreaSeries
    \brief The QAreaSeries class is used for making area charts.

    \mainclass

    An area chart is used to show quantitative data. It is based on line chart, in the way that area between axis and the line
    is emphasized with color. Since the area chart is based on line chart, QAreaSeries constructor needs QLineSeries instance,
    which defines "upper" boundary of the area. "Lower" boundary is defined by default by axis X. Instead of axis X "lower" boundary can be specified by other line.
    In that case QAreaSeries should be initiated with two QLineSeries instances. Please note terms "upper" and "lower" boundary can be misleading in cases
    where "lower" boundary had bigger values than the "upper" one, however the main point that area between these two boundary lines will be filled.

    See the \l {AreaChart Example} {area chart example} to learn how to create a simple area chart.
    \image examples_areachart.png
*/
/*!
    \qmlclass AreaSeries QAreaSeries

    The following QML shows how to create a simple area chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View4.qml 1
    \beginfloatleft
    \image demos_qmlchart4.png
    \endfloat
    \clearfloat
*/

/*!
   \property QAreaSeries::upperSeries
   \brief The upper one of the two line series used to define area series boundaries.
*/
/*!
   \qmlproperty LineSeries AreaSeries::upperSeries
   The upper one of the two line series used to define area series boundaries.
*/

/*!
    \property QAreaSeries::lowerSeries
    The lower one of the two line series used to define are series boundaries. Note if
    QAreaSeries was counstucted wihtout a\ lowerSeries this is null.
*/
/*!
    \qmlproperty LineSeries AreaSeries::lowerSeries
    The lower one of the two line series used to define are series boundaries. Note if
    AreaSeries was counstucted wihtout a\ lowerSeries this is null.
*/

/*!
    \property QAreaSeries::color
    Fill (brush) color of the series. This is a convenience property for modifying the color of brush.
    \sa QAreaSeries::brush()
*/
/*!
    \qmlproperty color AreaSeries::color
    Fill (brush) color of the series.
*/

/*!
    \property QAreaSeries::borderColor
    Line (pen) color of the series. This is a convenience property for modifying the color of pen.
    \sa QAreaSeries::pen()
*/
/*!
    \qmlproperty color AreaSeries::borderColor
    Line (pen) color of the series.
*/

/*!
    \qmlproperty real AreaSeries::borderWidth
    The width of the border line. By default the width is 2.0.
*/

/*!
   \fn QPen QAreaSeries::pen() const
   \brief  Returns the pen used to draw line for this series.
    \sa setPen()
*/

/*!
   \fn QPen QAreaSeries::brush() const
   \brief  Returns the brush used to draw line for this series.
    \sa setBrush()
*/

/*!
    \fn void QAreaSeries::colorChanged(QColor color)
    \brief Signal is emitted when the fill (brush) color has changed to \a color.
*/
/*!
    \qmlsignal AreaSeries::onColorChanged(color color)
    Signal is emitted when the fill (brush) color has changed to \a color.
*/

/*!
    \fn void QAreaSeries::borderColorChanged(QColor color)
    \brief Signal is emitted when the line (pen) color has changed to \a color.
*/
/*!
    \qmlsignal AreaSeries::onBorderColorChanged(color color)
    Signal is emitted when the line (pen) color has changed to \a color.
*/

/*!
    \fn void QAreaSeries::clicked(const QPointF& point)
    \brief Signal is emitted when user clicks the \a point on area chart.
*/
/*!
    \qmlsignal AreaSeries::onClicked(QPointF point)
    Signal is emitted when user clicks the \a point on area chart.
*/

/*!
    \fn void QAreaSeries::selected()
    The signal is emitted if the user selects/deselects the XY series. The logic for maintaining selections should be
    implemented by the user of QAreaSeries API.
*/
/*!
    \qmlsignal AreaSeries::onSelected()
    The signal is emitted if the user selects/deselects the XY series. The logic for maintaining selections should be
    implemented by the user of AreaSeries API.
*/

/*!
    \fn void QAreaSeriesPrivate::updated()
    \brief \internal
*/

/*!
    Constructs area series object which is a child of \a upperSeries. Area will be spanned between \a
    upperSeries line and \a lowerSeries line.  If no \a lowerSeries is passed to constructor, area is specified by axis x (y=0) instead.
    When series object is added to QChartView or QChart instance ownerships is transferred.
*/
QAreaSeries::QAreaSeries(QLineSeries *upperSeries, QLineSeries *lowerSeries)
    : QAbstractSeries(*new QAreaSeriesPrivate(upperSeries, lowerSeries, this), upperSeries)
{
}

/*!
    Constructs area series object without upper or lower series with \a parent object.
*/
QAreaSeries::QAreaSeries(QObject *parent)
    : QAbstractSeries(*new QAreaSeriesPrivate(0, 0, this), parent)
{
}

/*!
    Destroys the object.
*/
QAreaSeries::~QAreaSeries()
{
    Q_D(QAreaSeries);
    if (d->m_dataset)
        d->m_dataset->removeSeries(this);
}

/*!
    Returns QChartSeries::SeriesTypeArea.
*/
QAbstractSeries::SeriesType QAreaSeries::type() const
{
    return QAbstractSeries::SeriesTypeArea;
}

/*!
    Sets the \a series that is to be used as the area chart upper series.
*/
void QAreaSeries::setUpperSeries(QLineSeries *series)
{
    Q_D(QAreaSeries);
    d->m_upperSeries = series;
}

QLineSeries *QAreaSeries::upperSeries() const
{
    Q_D(const QAreaSeries);
    return d->m_upperSeries;
}

/*!
    Sets the \a series that is to be used as the area chart lower series.
*/
void QAreaSeries::setLowerSeries(QLineSeries *series)
{
    Q_D(QAreaSeries);
    d->m_lowerSeries = series;
}

QLineSeries *QAreaSeries::lowerSeries() const
{
    Q_D(const QAreaSeries);
    return d->m_lowerSeries;
}

/*!
    Sets \a pen used for drawing area outline.
*/
void QAreaSeries::setPen(const QPen &pen)
{
    Q_D(QAreaSeries);
    if (d->m_pen != pen) {
        d->m_pen = pen;
        emit d->updated();
    }
}

QPen  QAreaSeries::pen() const
{
    Q_D(const QAreaSeries);
    return d->m_pen;
}

/*!
    Sets \a brush used for filling the area.
*/
void QAreaSeries::setBrush(const QBrush &brush)
{
    Q_D(QAreaSeries);
    if (d->m_brush != brush) {
        bool emitColorChanged = brush.color() != d->m_brush.color();
        d->m_brush = brush;
        emit d->updated();
        if (emitColorChanged)
            emit colorChanged(brush.color());
    }
}

QBrush QAreaSeries::brush() const
{
    Q_D(const QAreaSeries);
    return d->m_brush;
}

void QAreaSeries::setColor(const QColor &color)
{
    QBrush b = brush();
    if (b == QBrush())
        b.setStyle(Qt::SolidPattern);
    b.setColor(color);
    setBrush(b);
}

QColor QAreaSeries::color() const
{
    return brush().color();
}

void QAreaSeries::setBorderColor(const QColor &color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
        emit borderColorChanged(color);
    }
}

QColor QAreaSeries::borderColor() const
{
    return pen().color();
}

/*!
    Sets if data points are \a visible and should be drawn on line.
*/
void QAreaSeries::setPointsVisible(bool visible)
{
    Q_D(QAreaSeries);
    if (d->m_pointsVisible != visible) {
        d->m_pointsVisible = visible;
        emit d->updated();
    }
}

/*!
    Returns if the points are drawn for this series.
    \sa setPointsVisible()
*/
bool QAreaSeries::pointsVisible() const
{
    Q_D(const QAreaSeries);
    return d->m_pointsVisible;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAreaSeriesPrivate::QAreaSeriesPrivate(QLineSeries *upperSeries, QLineSeries *lowerSeries, QAreaSeries *q)
    : QAbstractSeriesPrivate(q),
      m_upperSeries(upperSeries),
      m_lowerSeries(lowerSeries),
      m_pointsVisible(false)
{
}

void QAreaSeriesPrivate::scaleDomain(Domain &domain)
{
    Q_Q(QAreaSeries);

    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());

    QLineSeries *upperSeries = q->upperSeries();
    QLineSeries *lowerSeries = q->lowerSeries();

    const QList<QPointF>& points = upperSeries->points();

    for (int i = 0; i < points.count(); i++) {
        qreal x = points[i].x();
        qreal y = points[i].y();
        minX = qMin(minX, x);
        minY = qMin(minY, y);
        maxX = qMax(maxX, x);
        maxY = qMax(maxY, y);
    }
    if (lowerSeries) {

        const QList<QPointF>& points = lowerSeries->points();

        for (int i = 0; i < points.count(); i++) {
            qreal x = points[i].x();
            qreal y = points[i].y();
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
        }
    }

    domain.setRange(minX, maxX, minY, maxY);
}

ChartElement *QAreaSeriesPrivate::createGraphics(ChartPresenter *presenter)
{
    Q_Q(QAreaSeries);

    AreaChartItem *area = new AreaChartItem(q, presenter);
    if (presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        area->upperLineItem()->setAnimation(new XYAnimation(area->upperLineItem()));
        if (q->lowerSeries())
            area->lowerLineItem()->setAnimation(new XYAnimation(area->lowerLineItem()));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return area;
}

QList<QLegendMarker*> QAreaSeriesPrivate::createLegendMarkers(QLegend* legend)
{
    Q_Q(QAreaSeries);
    QList<QLegendMarker*> list;
    return list << new QAreaLegendMarker(q,legend);
}

void QAreaSeriesPrivate::initializeAxis(QAbstractAxis *axis)
{
    Q_UNUSED(axis);
}

QAbstractAxis::AxisType QAreaSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return QAbstractAxis::AxisTypeValue;
}

#include "moc_qareaseries.cpp"
#include "moc_qareaseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
