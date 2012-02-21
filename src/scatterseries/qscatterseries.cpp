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
    \class QScatterSeries
    \brief QtCommercial Chart series API for showing scatter series.

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
QScatterSeries::QScatterSeries(QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate())
{
}

/*!
    Destructor
*/
QScatterSeries::~QScatterSeries()
{
    delete d;
}

/*!
    Add single data point to the series.
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
    returns the current list of data points of the series.
*/
QList<QPointF> QScatterSeries::data()
{
    return d->m_data;
}

/*!
    Customizes the graphical presentation of the marker items. Replaces the default pen used for
    drawing a marker item with a user defined pen.
*/
void QScatterSeries::setMarkerPen(QPen pen)
{
    d->m_markerPen = pen;
}

/*!

*/
QPen QScatterSeries::markerPen()
{
    return d->m_markerPen;
}

void QScatterSeries::setMarkerBrush(QBrush brush)
{
    d->m_markerBrush = brush;
}

QBrush QScatterSeries::markerBrush()
{
    return d->m_markerBrush;
}

void QScatterSeries::setMarkerShape(MarkerShape shape)
{
    d->m_markerShape = shape;
}

QScatterSeries::MarkerShape QScatterSeries::markerShape()
{
    return (QScatterSeries::MarkerShape) d->m_markerShape;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
