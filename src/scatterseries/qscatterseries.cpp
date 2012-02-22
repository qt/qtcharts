#include "qscatterseries.h"
#include "scatterseries_p.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QScatterSeriesPrivate::QScatterSeriesPrivate() :
    m_data(QList<QPointF>()),
    m_markerPen(QPen()),
    m_markerBrush(QBrush()),
    m_markerShape(QScatterSeries::MarkerShapeDefault)
{
    // Initialize pen color to invalid to use a theme color by default
    m_markerPen.setColor(QColor::Invalid);
    m_markerBrush.setColor(QColor::Invalid);
}

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
    \class QScatterSeries
    \brief QtCommercial Chart series API for showing scatter series.

    \snippet ../../example/scatter/main.cpp 1
    Example on how to create a chart with scatter series:
    \code
    #include <qchartglobal.h>
    #include <qchartview.h>
    #include <qscatterseries.h>
    ...
    QTCOMMERCIALCHART_USE_NAMESPACE

    // Create chart widget
    QChartView *chartView = new QChartView();
    QScatterSeries *scatter = new QScatterSeries();
    *scatter << QPointF(0.5, 5.0) << QPointF(1.0, 4.5) << QPointF(1.0, 5.5) << QPointF(1.5, 5.0);
    chartView->addSeries(scatter);
    // Then add the QChartView into a layout...
    \endcode

    The example code would result the following:

    \image scatter_example1.jpg
*/

/*!
    Constructs a series object which is a child of \a parent.
*/
QScatterSeries::QScatterSeries(QObject *parent) :
    QChartSeries(parent),
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
    Add single data point to the series.
    For example:
    \code
    mySeries.addData(QPointF(0.5, 5.0));
    \endcode
*/
void QScatterSeries::addData(QPointF value)
{
    d->m_data.append(value);
    emit changed();
}

/*!
    Stream operator for adding a data point to the series.
    \sa addData(), QScatterSeries::addData(QPointF value)

    For example:
    \code
    mySeries << QPointF(0.5, 5.0)
             << QPointF(1.0, 4.5);
    \endcode

*/
QScatterSeries& QScatterSeries::operator << (const QPointF &value)
{
    d->m_data.append(value);
    emit changed();
    return *this;
}

/*!
    Replaces the data of the series with the given list of data points.
*/
void QScatterSeries::setData(QList<QPointF> data)
{
    d->m_data = data;
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
    Overrides the default pen used for drawing a marker item with a user defined pen. The default
    pen is defined by chart theme setting.

    For example:
    \code
    QPen pen(QColor(0, 255, 0, 80), 3);
    myScatter->setMarkerPen(pen);
    \endcode

    Would present your scatter markers with an opaque, uglyish green outlines:
    \image scatter_example_pen.jpg

    \sa setMarkerBrush()
    \sa QChart::setTheme()
*/
void QScatterSeries::setMarkerPen(QPen pen)
{
    d->m_markerPen = pen;
}

/*!
    Returns the pen used for drawing markers.
*/
QPen QScatterSeries::markerPen()
{
    return d->m_markerPen;
}

/*!
    Overrides the default brush of the marker items with a user defined brush. The default
    brush is defined by chart theme setting.

    For example:
    \code
    QBrush brush(QColor(255, 0, 0, 100), Qt::SolidPattern);
    myRandomScatter->setMarkerBrush(brush);
    \endcode

    Would fill your scatter markers with an opaque red color:
    \image scatter_example_brush.jpg

    \sa setMarkerPen()
    \sa QChart::setTheme()
*/
void QScatterSeries::setMarkerBrush(QBrush brush)
{
    d->m_markerBrush = brush;
}

/*!
    Returns the brush used for drawing markers.
*/
QBrush QScatterSeries::markerBrush()
{
    return d->m_markerBrush;
}

/*!
    Overrides the default shape of the marker items with a user defined shape. The default
    shape is defined by chart theme setting.

    For example:
    \code
    myScatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    \endcode

    Would make your scatter marker items rectangle:
    \image scatter_example_shape.jpg
*/
void QScatterSeries::setMarkerShape(MarkerShape shape)
{
    d->m_markerShape = shape;
}

/*!
    Returns the shape used for drawing markers.
*/
QScatterSeries::MarkerShape QScatterSeries::markerShape()
{
    return (QScatterSeries::MarkerShape) d->m_markerShape;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
