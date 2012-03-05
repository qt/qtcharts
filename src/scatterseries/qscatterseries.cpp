#include "qscatterseries.h"
#include "scatterseries_p.h"
#include "qchart.h"

/*!
    \class QScatterSeries
    \brief QtCommercial Chart series API for showing scatter series.

    \mainclass

    Example on how to create a chart with scatter series:
    \snippet ../example/scatter/main.cpp 1

    The example code would result the following:

    \image scatter_example1.jpg

    To customize the graphical representation of the series, you can modify pen, brush, shape and
    size of the marker items. For example:

    \snippet ../example/scatter/main.cpp 3

    Would present your scatter markers as big rectangles with opaque, uglyish green outlines and
    opaque red filling instead of the beatiful markers defined by the chart's theme:
    \image scatter_example_custom.jpg
*/

/*!
    \enum QScatterSeries::MarkerShape

    This enum describes the shape used when rendering marker items.

    \value MarkerShapeDefault
    \value MarkerShapeX
    \value MarkerShapeRectangle
    \value MarkerShapeRoundedRectangle
    \value MarkerShapeTiltedRectangle
    \value MarkerShapeTriangle
    \value MarkerShapeCircle
*/

/*!
    \fn QChartSeriesType QScatterSeries::type() const
    \brief Returns QChartSeries::SeriesTypeScatter.
*/

/*!
    \fn void QScatterSeries::clicked(QPointF coordinate)
    User clicked the scatter series. Note that the \a coordinate is the chart coordinate that the
    click occurred on; not necessarily a data point coordinate. To find the corresponding (closest)
    data point you can use closestPoint().
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QScatterSeriesPrivate::QScatterSeriesPrivate(QObject *parent) :
    QObject(parent),
    m_data(QList<QPointF>()),
    m_markerPen(QPen(QColor::Invalid)),
    m_markerBrush(QBrush(QColor::Invalid)),
    m_markerShape(QScatterSeries::MarkerShapeDefault),
    m_markerSize(9.0)
{
}

void QScatterSeriesPrivate::emitChanged()
{
    emit changed();
}

#include "moc_scatterseries_p.cpp"

/*!
    Constructs a series object which is a child of \a parent.
*/
QScatterSeries::QScatterSeries(QObject *parent) :
    QSeries(parent),
    d(new QScatterSeriesPrivate(this))
{
}

/*!
    Destroys the object. Note that adding series to QChart transfers the ownership to the chart.
*/
QScatterSeries::~QScatterSeries()
{
    delete d;
}

/*!
    Add single data point with \a x and \a y coordinates to the series.
*/
void QScatterSeries::add(qreal x, qreal y)
{
    d->m_data.append(QPointF(x, y));
    d->emitChanged();
}

/*!
    Add single data point with \a value to the series.
*/
void QScatterSeries::add(QPointF value)
{
    d->m_data.append(value);
    d->emitChanged();
}

/*!
    Add list of \a points to the series.
*/
void QScatterSeries::add(QList<QPointF> points)
{
    d->m_data.append(points);
    d->emitChanged();
}

/*!
    Stream operator for adding a data point with \a value to the series.
    \sa add()

    For example:
    \snippet ../example/scatter/main.cpp 2
*/
QScatterSeries& QScatterSeries::operator << (const QPointF &value)
{
    d->m_data.append(value);
    d->emitChanged();
    return *this;
}

/*!
    Stream operator for adding a list of points to the series.
    \sa add()
*/
QScatterSeries& QScatterSeries::operator << (QList<QPointF> value)
{
    d->m_data.append(value);
    d->emitChanged();
    return *this;
}

/*!
    Replaces the data of the series with the given list of data \a points.
*/
void QScatterSeries::setData(QList<QPointF> points)
{
    d->m_data = points;
    d->emitChanged();
}

/*!
    Returns the current list of data points of the series.
*/
QList<QPointF> QScatterSeries::data()
{
    return d->m_data;
}

/*!
    Replaces the point at \a index with \a newPoint. Returns true if \a index is a valid position
    in the series data, false otherwise.
*/
bool QScatterSeries::replace(int index, QPointF newPoint)
{
    if (index >= 0 && index < d->m_data.count()) {
        d->m_data.replace(index, newPoint);
        d->emitChanged();
        return true;
    }
    return false;
}

/*!
    Remove the data point at \a index. Returns true if a point was removed, false if the point
    at \a index does not exist on the series.
*/
bool QScatterSeries::removeAt(int index)
{
    if (index >=0 && index < d->m_data.count()) {
        d->m_data.removeAt(index);
        d->emitChanged();
        return true;
    }
    return false;
}

/*!
    Remove all occurrences of \a point from the series and returns the number of points removed.
*/
int QScatterSeries::removeAll(QPointF point)
{
    int count = d->m_data.removeAll(point);
    d->emitChanged();
    return count;
}

/*!
    Remove all data points from the series.
*/
void QScatterSeries::clear()
{
    d->m_data.clear();
    d->emitChanged();
}

/*!
    Returns the index of the data point that is closest to \a coordinate. If several data points
    are at the same distance from the \a coordinate, returns the last one. If no points exist,
    returns -1.
*/
int QScatterSeries::closestPoint(QPointF coordinate)
{
    qreal distance(-1);
    int pointIndex(-1);
    for (int i(0); i < d->m_data.count(); i++) {
        QPointF dataPoint = d->m_data.at(i);
        QPointF difference = dataPoint - coordinate;
        if (i == 0 || difference.manhattanLength() <= distance) {
            distance = difference.manhattanLength();
            pointIndex = i;
        }
    }
    return pointIndex;
}

/*!
    Returns the pen used for drawing markers.
*/
QPen QScatterSeries::pen() const
{
    return d->m_markerPen;
}

/*!
    Overrides the default pen used for drawing a marker item with a user defined \a pen. The
    default pen is defined by chart theme setting.

    \sa setBrush()
    \sa QChart::setChartTheme()
*/
void QScatterSeries::setPen(const QPen &pen)
{
    d->m_markerPen = pen;
    d->emitChanged();
}

/*!
    Returns the brush used for drawing markers.
*/
QBrush QScatterSeries::brush() const
{
    return d->m_markerBrush;
}

/*!
    Overrides the default brush of the marker items with a user defined \a brush. The default brush
    is defined by chart theme setting.

    \sa setPen()
    \sa QChart::setChartTheme()
*/
void QScatterSeries::setBrush(const QBrush &brush)
{
    d->m_markerBrush = brush;
    d->emitChanged();
}

/*!
    Returns the shape used for drawing markers.
*/
QScatterSeries::MarkerShape QScatterSeries::shape() const
{
    return (QScatterSeries::MarkerShape) d->m_markerShape;
}

/*!
    Overrides the default shape of the marker items with a user defined \a shape. The default shape
    is defined by chart theme setting.
*/
void QScatterSeries::setShape(MarkerShape shape)
{
    d->m_markerShape = shape;
    d->emitChanged();
}

/*!
    Returns the size of the marker items.
*/
qreal QScatterSeries::size() const
{
    return d->m_markerSize;
}

/*!
    Set the \a size of the marker items. The default size is 9.0.
*/
void QScatterSeries::setSize(qreal size)
{
    d->m_markerSize = size;
    d->emitChanged();
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
