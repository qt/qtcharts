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
    m_model = NULL;
    m_mapCategories = -1;
    m_mapBarBottom = -1;
    m_mapBarTop = -1;
    m_mapOrientation = Qt::Vertical;
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
    connect(set, SIGNAL(valueChanged()), this, SLOT(barsetChanged()));
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
//    if(m_model)
//        return m_mapBarTop - m_mapBarBottom;
//    else
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

bool QBarSeries::setModel(QAbstractItemModel* model)
{
    // disconnect signals from old model
    if(m_model)
    {
        disconnect(m_model, 0, this, 0);
        m_mapCategories = -1;
        m_mapBarBottom = -1;
        m_mapBarTop = -1;
        m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if(model)
    {
        m_model = model;
        return true;
    }
    else
    {
        m_model = NULL;
        return false;
    }
}

// TODO
void QBarSeries::setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation)
{
    if (m_model == NULL)
        return;
    m_mapCategories = categories;
    m_mapBarBottom = bottomBoundry;
    m_mapBarTop = topBoundry;
    m_mapOrientation = orientation;

    // connect the signals
    if (m_mapOrientation == Qt::Vertical)
    {
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }
    else
    {
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(columnsInserted(QModelIndex, int, int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(columnsRemoved(QModelIndex, int, int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }


    // create the initial bars
    delete mModel;
    if (m_mapOrientation == Qt::Vertical)
    {
        QStringList categories;
        for (int k = 0; k < m_model->rowCount(); k++)
            categories << m_model->data(m_model->index(k, m_mapCategories), Qt::DisplayRole).toString();
        mModel = new BarChartModel(categories, this);

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++)
        {
            QBarSet* barSet = new QBarSet(QString("Column: %1").arg(i + 1));
            for(int m = 0; m < m_model->rowCount(); m++)
                *barSet << m_model->data(m_model->index(m, i), Qt::DisplayRole).toDouble();
            addBarSet(barSet);
        }
    }
    else
    {
        QStringList categories;
        for (int k = 0; k < m_model->columnCount(); k++)
            categories << m_model->data(m_model->index(m_mapCategories, k), Qt::DisplayRole).toString();
        mModel = new BarChartModel(categories, this);

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++)
        {
            QBarSet* barSet = new QBarSet(QString("Row: %1").arg(i + 1));
            for(int m = 0; m < m_model->columnCount(); m++)
                *barSet << m_model->data(m_model->index(i, m), Qt::DisplayRole).toDouble();
            addBarSet(barSet);
        }
    }
}

void QBarSeries::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    Q_UNUSED(bottomRight)

    if (m_mapOrientation == Qt::Vertical)
    {
        if (topLeft.column() >= m_mapBarBottom && topLeft.column() <= m_mapBarTop)
            barsetAt(topLeft.column() - m_mapBarBottom)->setValue(topLeft.row(), m_model->data(topLeft, Qt::DisplayRole).toDouble());
//        else if (topLeft.column() == m_mapCategories)
//            slices().at(topLeft.row())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
    }
    else
    {
        if (topLeft.row() >= m_mapBarBottom && topLeft.row() <= m_mapBarTop)
            barsetAt(topLeft.row() - m_mapBarBottom)->setValue(topLeft.column(), m_model->data(topLeft, Qt::DisplayRole).toDouble());
//        else if (topLeft.row() == m_mapCategories)
//            slices().at(topLeft.column())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
    }
}

void QBarSeries::modelDataAdded(QModelIndex /*parent*/, int /*start*/, int /*end*/)
{
    //
}

void QBarSeries::modelDataRemoved(QModelIndex /*parent*/, int /*start*/, int /*end*/)
{
    //
}

void QBarSeries::barsetChanged()
{
    emit updatedBars();
}

#include "moc_qbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
