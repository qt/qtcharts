#include "qpercentbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPercentBarSeries
    \brief part of QtCommercial chart API.

    QPercentBarSeries represents a series of data shown as bars. Each bar of QBarSet is shown as percentage
    of all bars in category. One QPercentBarSeries can contain multible QBarSet data sets.
    QBarSeries groups the data from sets to categories, which are defined by QBarCategory class.

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

    \sa QBarCategory, QBarSet, QStackedBarSeries, QBarSeries
*/

/*!
    \fn virtual QChartSeriesType QPercentBarSeries::type() const
    \brief Returns type of series.
    \sa QChartSeries, QChartSeriesType
*/

/*!
    Constructs empty QPercentBarSeries. Parameter \a category defines the categories for chart.
    QPercentBarSeries is QObject which is a child of a \a parent.
*/
QPercentBarSeries::QPercentBarSeries(QBarCategory *category, QObject *parent)
    : QBarSeries(category, parent)
{
}

#include "moc_qpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

