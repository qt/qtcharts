#include <QDebug>
#include "qbarseries.h"
#include "qbarcategory.h"
#include "qbarset.h"
#include "barchartmodel_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \brief part of QtCommercial chart API.

    QBarSeries represents a series of data shown as bars. One QBarSeries can contain multible
    QBarSet data sets. QBarSeries groups the data from sets to categories, which are defined
    by QBarCategory class.

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

    \sa QBarCategory, QBarSet, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn virtual QChartSeriesType QBarSeries::type() const
    \brief Returns type of series.
    \sa QChartSeries, QChartSeriesType
*/
/*!
    \fn void QBarSeries::changed(int index)
    \brief \internal \a index
*/
/*!
    \fn void QBarSeries::floatingValuesEnabled(bool enabled)
    \brief \internal \a enabled
*/
/*!
    \fn void QBarSeries::toolTipEnabled(bool enabled)
    \brief \internal \a enabled
*/
/*!
    \fn void QBarSeries::separatorsEnabled(bool enabled)
    \brief \internal \a enabled
*/
/*!
    \fn void QBarSeries::showToolTip(QPoint pos, QString tip)
    \brief \internal \a pos \a tip
*/

/*!
    Constructs empty QBarSeries. Parameter \a category defines the categories for chart.
    Takes ownership of \a category.
    QBarSeries is QObject which is a child of a \a parent.
*/
QBarSeries::QBarSeries(QBarCategory *category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
}

/*!
    Adds a set of bars to series. Takes ownership of \a set
*/
void QBarSeries::addBarSet(QBarSet *set)
{
    mModel->addBarSet(set);
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesnt delete \a set.
*/
void QBarSeries::removeBarSet(QBarSet *set)
{
    mModel->removeBarSet(set);
}

/*!
    Returns number of sets in series.
*/
int QBarSeries::countSets()
{
    return mModel->countSets();
}

/*!
    Returns number of categories in series
*/
int QBarSeries::countCategories()
{
    return mModel->countCategories();
}

/*!
    Simple iterator for set. Returns pointer to next set in series.
    Returns first set, if parameter \a getFirst is true.
    If series is empty, returns 0.
    Returns 0 after last set.
*/
QBarSet* QBarSeries::nextSet(bool getFirst)
{
    return mModel->nextSet(getFirst);
}

/*!
    Returns set indexed by \a index. Doesn't check for index bounds.
    Assumes that \a index is between 0 and number of sets. Use countSets() to get valid index bound.
    \sa countSets()
*/
QBarSet* QBarSeries::setAt(int index)
{
    return mModel->setAt(index);
}

/*!
    Returns legend of series. Legend is a list of set names in series.
*/
QList<QString> QBarSeries::legend()
{
    return mModel->legend();
}

/*!
    \internal \a category
*/
QString QBarSeries::label(int category)
{
    return mModel->label(category);
}

/*!
    Enables or disables floating values depending on parameter \a enabled.
    Floating values are bar values, that are displayed on top of each bar.
    Calling without parameter \a enabled, enables the floating values
*/
void QBarSeries::enableFloatingValues(bool enabled)
{
    if (enabled) {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            connect(set,SIGNAL(clicked()),set,SIGNAL(toggleFloatingValues()));
        }
    } else {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            disconnect(set,SIGNAL(clicked()),set,SIGNAL(toggleFloatingValues()));
        }
    }
}

/*!
    Enables or disables tooltip depending on parameter \a enabled.
    Tooltip shows the name of set, when mouse is hovering on top of bar.
    Calling without parameter \a enabled, enables the tooltip
*/
void QBarSeries::enableToolTip(bool enabled)
{
    if (enabled) {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            connect(set,SIGNAL(showToolTip(QPoint,QString)),this,SIGNAL(showToolTip(QPoint,QString)));
        }
    } else {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            disconnect(set,SIGNAL(showToolTip(QPoint,QString)),this,SIGNAL(showToolTip(QPoint,QString)));
        }
    }
}

/*!
    Enables or disables separators depending on parameter \a enabled.
    Separators are visual elements that are drawn between categories.
    Calling without parameter \a enabled, enables the separators
*/
void QBarSeries::enableSeparators(bool enabled)
{
    emit separatorsEnabled(enabled);
}

/*!
    \internal
*/
qreal QBarSeries::min()
{
    return mModel->min();
}

/*!
    \internal
*/
qreal QBarSeries::max()
{
    return mModel->max();
}

/*!
    \internal \a set \a category
*/
qreal QBarSeries::valueAt(int set, int category)
{
    return mModel->valueAt(set,category);
}

/*!
    \internal \a set \a category
*/
qreal QBarSeries::percentageAt(int set, int category)
{
    return mModel->percentageAt(set,category);
}

/*!
    \internal \a category
*/
qreal QBarSeries::categorySum(int category)
{
    return mModel->categorySum(category);
}

/*!
    \internal
*/
qreal QBarSeries::maxCategorySum()
{
    return mModel->maxCategorySum();
}

/*!
    \internal
*/
BarChartModel& QBarSeries::model()
{
    return *mModel;
}

#include "moc_qbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
