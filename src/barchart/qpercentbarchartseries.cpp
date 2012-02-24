#include "qpercentbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPercentBarChartSeries
    \brief part of QtCommercial chart API.

    QPercentBarChartSeries represents a series of data shown as bars. Each bar of QBarSet is shown as percentage
    of all bars in category. One QPercentBarChartSeries can contain multible QBarSet data sets.
    QBarChartSeries groups the data from sets to categories, which are defined by QBarCategory class.

    \mainclass

    Example on using QPercentBarChartSeries
    \snippet ../example/percentbarchart/main.cpp 1

    \sa QBarCategory, QBarSet, QStackedBarChartSeries, QBarChartSeries
*/

/*!
    \fn virtual QChartSeriesType QPercentBarChartSeries::type() const
    \brief Returns type of series.
    \sa QChartSeries, QChartSeriesType
*/

/*!
    Constructs empty QPercentBarChartSeries. Parameter \a category defines the categories for chart.
    QPercentBarChartSeries is QObject which is a child of a \a parent.
*/
QPercentBarChartSeries::QPercentBarChartSeries(QBarCategory *category, QObject *parent)
    : QBarChartSeries(category, parent)
{
}

#include "moc_qpercentbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

