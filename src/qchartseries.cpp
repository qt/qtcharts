#include "qchartseries.h"

/*!
    \class QChartSeries
    \brief Base class for all QtCommercial Chart series.
    \mainclass
*/

/*!
    \enum QChartSeries::QChartSeriesType

    The type of the series object.

    \value SeriesTypeLine
    \value SeriesTypeArea
    \value SeriesTypeBar
    \value SeriesTypeStackedBar
    \value SeriesTypePercentBar
    \value SeriesTypePie
    \value SeriesTypeScatter
    \value SeriesTypeSpline
*/

/*!
    \fn QChartSeries::QChartSeries(QObject *parent)
    \brief Constructs ChartSeries object with \a parent.
*/

/*!
    \fn QChartSeries::~QChartSeries()
    \brief Virtual destructor for the chart series.
*/

/*!
    \fn QChartSeriesType QChartSeries::type() const
    \brief The type of the series.
*/

/*!
    \fn bool QChartSeries::setModel(QAbstractItemModel *model)
    \brief Use the \a model to provide data for the series. The model overrides possible user data
    set with QChartSeries type specific data setters. For example if you call both
    QScatterSeries::addData() and QScatterSeries::setModel, only the data provided by the model is
    used by the series. Returns true if the model is valid for the series.
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE
#include "moc_qchartseries.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
