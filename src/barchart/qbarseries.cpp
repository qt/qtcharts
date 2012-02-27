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

    \sa QBarCategory, QBarSet, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn virtual QSeriesType QBarSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
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
    : QSeries(parent)
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
    Returns a list of sets in series. Keeps ownership of sets.
 */
QList<QBarSet*> QBarSeries::barSets()
{
    return mModel->barSets();
}

/*!
    \internal \a index
*/
QBarSet* QBarSeries::barsetAt(int index)
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
void QBarSeries::setFloatingValuesEnabled(bool enabled)
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
void QBarSeries::setToolTipEnabled(bool enabled)
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
void QBarSeries::setSeparatorsEnabled(bool enabled)
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
