#include "qseries.h"

/*!
    \class QSeries
    \brief Base class for all QtCommercial Chart series.
    \mainclass

    Usually you use the series type specific inherited classes instead of the base class.
    \sa QScatterSeries
*/

/*!
    \enum QSeries::QSeriesType

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
    \fn QSeries::QSeries(QObject *parent)
    \brief Constructs ChartSeries object with \a parent.
*/

/*!
    \fn QSeries::~QSeries()
    \brief Virtual destructor for the chart series.
*/

/*!
    \fn QSeriesType QSeries::type() const
    \brief The type of the series.
*/

/*!
    \fn bool QSeries::setModel(QAbstractItemModel *model)
    \brief Use the \a model to provide data for the series. The model overrides possible user data
    set with QChartSeries type specific data setters. For example if you call both
    QScatterSeries::addData() and QScatterSeries::setModel, only the data provided by the model is
    used by the series. Returns true if the model is valid for the series.
*/

/*!
    \fn void QSeries::setTitle(QString title)
    \brief Sets a \a title for the series.

    This is not used directly by the chart itself. It is up to the user to use this as for example
    chart title.
    \sa QChart::setChartTitle()
*/

/*!
    \fn QString QSeries::title()
    \brief Returns the title of the series.
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE
#include "moc_qseries.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
