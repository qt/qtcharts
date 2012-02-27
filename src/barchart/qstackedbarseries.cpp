#include "qstackedbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QStackedBarSeries
    \brief part of QtCommercial chart API.

    QStackedBarSeries represents a series of data shown as bars. All bars in same category are
    stacked on top of each other. One QStackedBarSeries can contain multible QBarSet data sets.
    QStackedBarSeries groups the data from sets to categories, which are defined by QBarCategory class.

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

    \sa QBarCategory, QBarSet, QPercentBarSeries, QBarSeries
*/

/*!
    \fn virtual QChartSeriesType QStackedBarSeries::type() const
    \brief Returns type of series.
    \sa QChartSeries, QChartSeriesType
*/

/*!
    Constructs empty QStackedBarSeries. Parameter \a category defines the categories for chart.
    QStackedBarSeries is QObject which is a child of a \a parent.
*/
QStackedBarSeries::QStackedBarSeries(QBarCategory *category, QObject *parent)
    : QBarSeries(category, parent)
{
}

#include "moc_qstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

