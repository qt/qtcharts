#include <QDebug>
#include "qbarseries.h"
#include "qbarset.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \brief part of QtCommercial chart API.

    QBarSeries represents a series of data shown as bars. One QBarSeries can contain multible
    QBarSet data sets. QBarSeries groups the data from sets to categories, which are defined
    by QStringList.

    \mainclass

    \sa QBarSet, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn virtual QSeriesType QBarSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
    \fn void QBarSeries::showToolTip(QPoint pos, QString tip)
    \brief \internal \a pos \a tip
*/

/*!
    Constructs empty QBarSeries. Parameter \a categories defines the categories for chart.
    QBarSeries is QObject which is a child of a \a parent.
*/
QBarSeries::QBarSeries(QStringList categories, QObject *parent)
    : QSeries(parent)
    ,mModel(new BarChartModel(categories, this))
{
}

/*!
    Adds a set of bars to series. Takes ownership of \a set.
    Connects the clicked(QString) and rightClicked(QString) signals
    of \a set to this series
*/
void QBarSeries::addBarSet(QBarSet *set)
{
    mModel->addBarSet(set);
    connect(set,SIGNAL(clicked(QString)),this,SLOT(barsetClicked(QString)));
    connect(set,SIGNAL(rightClicked(QString)),this,SLOT(barsetRightClicked(QString)));
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesnt delete \a set.
    Disconnects the clicked(QString) and rightClicked(QString) signals
    of \a set from this series
*/
void QBarSeries::removeBarSet(QBarSet *set)
{
    disconnect(set,SIGNAL(clicked(QString)),this,SLOT(barsetClicked(QString)));
    disconnect(set,SIGNAL(rightClicked(QString)),this,SLOT(barsetRightClicked(QString)));
    mModel->removeBarSet(set);
}

/*!
    Returns number of sets in series.
*/
int QBarSeries::barsetCount()
{
    if(m_model)
        return m_mapBarTop - m_mapBarBottom;
    else
        return mModel->barsetCount();
}

/*!
    Returns number of categories in series
*/
int QBarSeries::categoryCount()
{
    return mModel->categoryCount();
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
    Returns legend of series.
*/
QList<QSeries::LegendEntry> QBarSeries::legendEntries()
{
    return mModel->legendEntries();
}

/*!
    \internal \a category
*/
QString QBarSeries::categoryName(int category)
{
    return mModel->categoryName(category);
}

/*!
    Enables or disables tooltip depending on parameter \a enabled.
    Tooltip shows the name of set, when mouse is hovering on top of bar.
    Calling without parameter \a enabled, enables the tooltip
*/
void QBarSeries::setToolTipEnabled(bool enabled)
{
    // TODO: what if we add sets after call to this function? Those sets won't have tooltip enabled.
    if (enabled) {
        for (int i=0; i<mModel->barsetCount(); i++) {
            QBarSet *set = mModel->setAt(i);
            connect(set,SIGNAL(showToolTip(QPoint,QString)),this,SIGNAL(showToolTip(QPoint,QString)));
        }
    } else {
        for (int i=0; i<mModel->barsetCount(); i++) {
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
void QBarSeries::setSeparatorsVisible(bool visible)
{
    mSeparatorsVisible = visible;
    emit enableSeparators(visible);
}


/*!
    \internal \a category
*/
void QBarSeries::barsetClicked(QString category)
{
    emit clicked(qobject_cast<QBarSet*>(sender()), category);
}

/*!
    \internal \a category
*/
void QBarSeries::barsetRightClicked(QString category)
{
    emit rightClicked(qobject_cast<QBarSet*>(sender()), category);
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

bool QBarSeries::separatorsVisible()
{
    return mSeparatorsVisible;
}

bool QBarSeries::setModel(QAbstractItemModel* model)
{
    m_model = model;
}

void QBarSeries::setModelMappingCategories(int modelColumn)
{
    //
}

void QBarSeries::setModelMappingBarRange(int bottomBoundry, int topBoundry)
{
    //
}

#include "moc_qbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
