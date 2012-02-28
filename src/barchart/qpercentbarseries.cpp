#include "qpercentbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPercentBarSeries
    \brief part of QtCommercial chart API.

    QPercentBarSeries represents a series of data shown as bars. Each bar of QBarSet is shown as percentage
    of all bars in category. One QPercentBarSeries can contain multible QBarSet data sets.
    QBarSeries groups the data from sets to categories, which are defined by QStringList.

    \mainclass

    \sa QBarSet, QStackedBarSeries, QBarSeries
*/

/*!
    \fn virtual QSeriesType QPercentBarSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
    Constructs empty QPercentBarSeries. Parameter \a category defines the categories for chart.
    QPercentBarSeries is QObject which is a child of a \a parent.
*/
QPercentBarSeries::QPercentBarSeries(QStringList categories, QObject *parent)
    : QBarSeries(categories, parent)
{
}

#include "moc_qpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

