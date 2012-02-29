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
*/

/*!
    \enum QScatterSeries::MarkerShape

    This enum describes the shape used when rendering marker items.

    \value MarkerShapeDefault
    \value MarkerShapePoint
    \value MarkerShapeX
    \value MarkerShapeRectangle
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

/*!
    \fn void QScatterSeries::changed()
    \brief TODO
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QScatterSeriesPrivate::QScatterSeriesPrivate() :
    m_data(QList<QPointF>()),
    m_markerPen(QPen(QColor::Invalid)),
    m_markerBrush(QBrush(QColor::Invalid)),
    m_markerShape(QScatterSeries::MarkerShapeDefault)
{
}

/*!
    Constructs a series object which is a child of \a parent.
*/
QScatterSeries::QScatterSeries(QObject *parent) :
    QSeries(parent),
    d(new QScatterSeriesPrivate())
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
    emit changed();
}

/*!
    Add single data point with \a value to the series.
*/
void QScatterSeries::add(QPointF value)
{
    d->m_data.append(value);
    emit changed();
}

/*!
    Add list of \a points to the series.
*/
void QScatterSeries::add(QList<QPointF> points)
{
    d->m_data.append(points);
    emit changed();
}

/*!
    Stream operator for adding a data point with \a value to the series.
    \sa add()

    For example:
    \snippet ../example/scatter/main.cpp 3
*/
QScatterSeries& QScatterSeries::operator << (const QPointF &value)
{
    d->m_data.append(value);
    emit changed();
    return *this;
}

/*!
    Stream operator for adding a list of points to the series.
    \sa add()
*/
QScatterSeries& QScatterSeries::operator << (QList<QPointF> value)
{
    d->m_data.append(value);
    emit changed();
    return *this;
}

/*!
    Replaces the data of the series with the given list of data \a points.
*/
void QScatterSeries::setData(QList<QPointF> points)
{
    d->m_data = points;
    emit changed();
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
        emit changed();
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
        emit changed();
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
    emit changed();
    return count;
}

/*!
    Remove all data points from the series.
*/
void QScatterSeries::clear()
{
    d->m_data.clear();
    emit changed();
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
    Overrides the default pen used for drawing a marker item with a user defined \a pen. The
    default pen is defined by chart theme setting.

    For example:
    \snippet ../example/scatter/main.cpp 5

    Would present your scatter markers with an opaque, uglyish green outlines instead of the
    beatiful markers defined by the chart's theme:
    \image scatter_example_pen.jpg

    \sa setBrush()
    \sa QChart::setChartTheme()
*/
void QScatterSeries::setPen(QPen pen)
{
    d->m_markerPen = pen;
}

/*!
    Returns the pen used for drawing markers.
*/
QPen QScatterSeries::pen()
{
    return d->m_markerPen;
}

/*!
    Overrides the default brush of the marker items with a user defined \a brush. The default brush
    is defined by chart theme setting.

    For example:
    \snippet ../example/scatter/main.cpp 4

    Would fill your scatter markers with an opaque red color:
    \image scatter_example_brush.jpg

    \sa setPen()
    \sa QChart::setChartTheme()
*/
void QScatterSeries::setBrush(QBrush brush)
{
    d->m_markerBrush = brush;
}

/*!
    Returns the brush used for drawing markers.
*/
QBrush QScatterSeries::brush()
{
    return d->m_markerBrush;
}

/*!
    Overrides the default shape of the marker items with a user defined \a shape. The default shape
    is defined by chart theme setting.

    For example:
    \snippet ../example/scatter/main.cpp 6

    Would make your scatter marker items rectangle:
    \image scatter_example_shape.jpg
*/
void QScatterSeries::setShape(MarkerShape shape)
{
    d->m_markerShape = shape;
}

/*!
    Returns the shape used for drawing markers.
*/
QScatterSeries::MarkerShape QScatterSeries::shape()
{
    return (QScatterSeries::MarkerShape) d->m_markerShape;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
