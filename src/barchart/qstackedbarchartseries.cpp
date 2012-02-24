#include "qstackedbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QStackedBarChartSeries
    \brief part of QtCommercial chart API.

    QStackedBarChartSeries represents a series of data shown as bars. All bars in same category are
    stacked on top of each other. One QStackedBarChartSeries can contain multible QBarSet data sets.
    QStackedBarChartSeries groups the data from sets to categories, which are defined by QBarCategory class.

    \mainclass

    Example on how to create category:
    \snippet ../example/barchart/main.cpp 1

    Example on how to create sets of data:
    \snippet ../example/barchart/main.cpp 2

    Example on how to add sets to bar chart:
    \snippet ../example/barchart/main.cpp 3

    Example on how to enable tooltip and floating values:
    \snippet ../example/barchart/main.cpp 4

    Example on how to create view and apply theme:
    \snippet ../example/barchart/main.cpp 5

    \sa QBarCategory, QBarSet, QPercentBarChartSeries, QBarChartSeries
*/

/*!
    \fn virtual QChartSeriesType QStackedBarChartSeries::type() const
    \brief Returns type of series.
    \sa QChartSeries, QChartSeriesType
*/

/*!
    Constructs empty QStackedBarChartSeries. Parameter \a category defines the categories for chart.
    QStackedBarChartSeries is QObject which is a child of a \a parent.
*/
QStackedBarChartSeries::QStackedBarChartSeries(QBarCategory *category, QObject *parent)
    : QBarChartSeries(category, parent)
{
}

#include "moc_qstackedbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

