#include "qstackedbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QStackedBarSeries
    \brief part of QtCommercial chart API.

    QStackedBarSeries represents a series of data shown as bars. All bars in same category are
    stacked on top of each other. One QStackedBarSeries can contain multible QBarSet data sets.
    QStackedBarSeries groups the data from sets to categories, which are defined by QStringList.

    \mainclass

    \sa QBarSet, QPercentBarSeries, QBarSeries
*/

/*!
    \fn virtual QSeriesType QStackedBarSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
    Constructs empty QStackedBarSeries. Parameter \a category defines the categories for chart.
    QStackedBarSeries is QObject which is a child of a \a parent.
*/
QStackedBarSeries::QStackedBarSeries(QStringList categories, QObject *parent)
    : QBarSeries(categories, parent)
{
}

#include "moc_qstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

