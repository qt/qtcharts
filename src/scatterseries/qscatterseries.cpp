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

QScatterSeries::QScatterSeries(QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate())
{
}

QScatterSeries::~QScatterSeries()
{
    delete d;
}

void QScatterSeries::addData(QPointF value)
{
    d->m_data.append(value);
    emit changed();
}

QScatterSeries& QScatterSeries::operator << (const QPointF &value)
{
    d->m_data.append(value);
    emit changed();
    return *this;
}

void QScatterSeries::setData(QList<QPointF> data)
{
    d->m_data = data;
    emit changed();
}

QList<QPointF> QScatterSeries::data()
{
    return d->m_data;
}

void QScatterSeries::setMarkerPen(QPen pen)
{
    d->m_markerPen = pen;
}

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
